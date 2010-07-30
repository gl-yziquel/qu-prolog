#!/usr/bin/env python

import wx,re,os

EVT_LAYOUT_ID = wx.NewId()
EVT_INDENT_ID = wx.NewId()

if wx.Platform == '__WXMSW__':
    face = 'Courier New'
    font_size = 10
else:
    face = 'Courier'
    font_size = 10




wildcard = "QuProlog Source (*.ql)|.ql |"\
    "Prolog Source (*.pl)|.pl"
    


class LayoutEvent(wx.PyEvent):
    def __init__(self):
        wx.PyEvent.__init__(self)
        self.SetEventType(EVT_LAYOUT_ID)

class IndentEvent(wx.PyEvent):
    def __init__(self, return_pressed, do_colour):
        wx.PyEvent.__init__(self)
        self.SetEventType(EVT_INDENT_ID)
        self.return_pressed = return_pressed
        self.do_colour = do_colour

re_order = ["comment1", "u_comment1", "comment2", 
            "string", "u_string", "char", "number",
            "var", "predicate","atom", "u_atom", "goal", "clause_end"]

punct = ['/*', '*/', ',', ';', '->', '(', ' (', '[', ']', ')', ':-', '\n']


all = re_order[2:] + punct

retable = {
    # comment 1
    "comment1":re.compile(r'/\*.*?\*/', re.M | re.S),
    # unfinished comment 1
    "u_comment1":re.compile(r'/\*.*', re.M | re.S),
    # comment 2
    "comment2":re.compile(r"""
    %[^\r^\n]*
    """, re.VERBOSE ),
    # strings
    "string":re.compile(r"""
    \"[^\"\\]*(?:\\.[^\"\\]*)*\"
    """, re.VERBOSE | re.M | re.S),
    # unfinished strings
    "u_string":re.compile(r"""
    \".*
    """, re.VERBOSE | re.M | re.S),
    # numbers
    "number":re.compile(r"""
    \d+
    (?:\.\d+)?(?:[eE][+-]?\d+)?
    """, re.VERBOSE | re.M),
    # vars
    "var":re.compile(r"""
    [A-Z][A-Za-z0-9_]*
    """, re.VERBOSE | re.M),
    # 0'c
    "char":re.compile(r"""
    0'.
    """, re.VERBOSE | re.M | re.S),
    # for atom tokens
    "atom":re.compile(r"""
    '[^'\\]*(?:\\.[^'\\]*)*'
    """, re.VERBOSE | re.M | re.S),
    # for unfinished atom tokens
    "u_atom":re.compile(r"""
    '.*
    """, re.VERBOSE | re.M | re.S),
    # pred defns
    "predicate":re.compile(r"""
    ^[a-z][A-Za-z0-9_]*
    """,  re.VERBOSE | re.M),
    # goal defns
    "goal":re.compile(r"""
    ^\?- | 
    ^\:-
    """,  re.VERBOSE | re.M),
    # end of clause
    "clause_end":re.compile(r"""
    \.\s
    """, re.VERBOSE | re.M | re.S),
    # comma
    ",":re.compile(r"""
    ,
    """, re.VERBOSE | re.M | re.S),
    # :-
    ":-":re.compile(r"""
    :-
    """, re.VERBOSE | re.M | re.S),
    # semi
    ";":re.compile(r"""
    ;
    """, re.VERBOSE | re.M | re.S),
    # if
    "->":re.compile(r"""
    ->
    """, re.VERBOSE | re.M | re.S),
    # /*
    "/*":re.compile(r"""
    /\*
    """, re.VERBOSE | re.M | re.S),
    # */
    "*/":re.compile(r"""
    \*/
    """, re.VERBOSE | re.M | re.S),
    # space (
    " (":re.compile(r"""
    \(
    """, re.VERBOSE | re.M | re.S),
    # (
    "(":re.compile(r"""
    (?<!\s)\(
    """, re.VERBOSE | re.M | re.S),
    # [
    "[":re.compile(r"""
    \[
    """, re.VERBOSE | re.M | re.S),
    # )
    ")":re.compile(r"""
    \)
    """, re.VERBOSE | re.M | re.S),
    # ]
    "]":re.compile(r"""
    \]
    """, re.VERBOSE | re.M | re.S),
    # \n
    "\n":re.compile(r"""
    \n
    """, re.VERBOSE | re.M | re.S)
    
    }

colours = {
    "comment1":"red",
    "u_comment1":"red",
    "comment2":"red",
    "string":"orange",
    "u_string":"orange",
    "number":"green",
    "var":"blue",
    "char":"cyan",
    "atom":"cyan",
    "u_atom":"cyan",
    "predicate":"violet",
    "goal":"black",
    "clause_end":"black"
    }

def string_diff(string1, string2):
    len1 = len(string1)
    len2 = len(string2)
    if len1 == len2:
        return (0, 0, '')
    if len1 > len2:
        first = 0
        while first < len2:
            if string1[first] != string2[first]:
                break
            first += 1
        return (1, first, string1[first:(first + (len1 - len2))])
    else:
        first = 0
        while first < len1:
            if string1[first] != string2[first]:
                break
            first += 1
        return (-1, first, string2[first:(first + (len2 - len1))])


class Matcher:
    def __init__(self, type, rematch, order):
        self.type = type
        self.rematch = rematch
        self.order = order

    def __gt__(self, other):
        if not self.rematch:
            return True
        if not other.rematch:
            return False
        return (self.rematch.start() > other.rematch.start()) or \
            (self.rematch.start() == other.rematch.start()) and \
            (self.order.index(self.type) > self.order.index(other.type))
    

    def __repr__(self):
        if self.rematch:
            return "%s:(%d, %d)" % (self.type, self.rematch.start(), 
                                    self.rematch.end())
        else:
            return "None"


class EditorWindow(wx.TextCtrl):
    def __init__(self, parent):
        wx.TextCtrl.__init__(self, parent, style=wx.TE_MULTILINE|wx.TE_RICH2)
        font = wx.Font(font_size, wx.MODERN, wx.NORMAL, wx.NORMAL)
        self.parent = parent
        self.SetFont(font)
        width,height =  self.GetTextExtent(80*'a')
        self.SetSize((width,height*30))

        self.Bind(wx.EVT_CHAR, self.char_event, self)
        self.Bind(wx.EVT_TEXT, self.text_updated, self)
        self.Bind(wx.EVT_LEFT_DOWN, self.left_down, self)
        self.Connect(-1, -1, EVT_LAYOUT_ID, self.enter)
        self.Connect(-1, -1, EVT_INDENT_ID, self.do_indent)
        font = wx.Font(font_size, wx.MODERN, wx.NORMAL, wx.NORMAL)
        self.SetFont(font)
        width,height =  self.GetTextExtent(80*'a')
        #self.SetSize((width,height*30))
        self.clause_ends = []
        self.return_pressed = False
        self.doing_return = False
        self.file = None
        self.undo = []
        self.undo_order = []
        self.undo_pos = -1
        self.previous = ''
        self.change = False

    def left_down(self, e):
        self.push_undo()
        e.Skip()

    def CanUndo(self):
        return True


    def undo_step(self, type, start, text, pos, direction):
        if type == 'delete' and direction == 1 or \
                type == 'insert' and direction == -1:
            self.SetInsertionPoint(start)
            self.WriteText(text)
            self.SetInsertionPoint(pos)
        else:
            self.Remove(start, start + len(text)) 
            self.SetInsertionPoint(start)


    def Undo(self):
        if self.change:
            self.push_undo()
        #print '----- undo ------', self.undo,self.undo_order,self.undo_pos
        if len(self.undo_order) > self.undo_pos >= 0:
            direction, undo_pos = self.undo_order[self.undo_pos]
            self.undo_pos -= 1
            stack = self.undo[undo_pos]
            if direction == 1:
                stack = list(stack)
                stack.reverse()
            for type, start, text, pos in stack:
                self.undo_step(type, start, text, pos, direction)
                #print type, start, text, pos, direction
            self.undo_order.append((-direction, undo_pos))
            self.do_enter(True)  
            #print '----- after undo ------', self.undo, self.undo_order,self.undo_pos
            self.previous = self.GetValue()
        if self.saved_text == self.GetValue():
            self.SetModified(False)
            if self.file:
                self.parent.SetTitle(self.file)

    def Cut(self):
        wx.TextCtrl.Cut(self)
        self.push_undo()
        self.do_enter(True)


    def Paste(self):
        pos = self.GetInsertionPoint()
        wx.TextCtrl.Paste(self)
        self.SetInsertionPoint(pos)
        self.push_undo()
        self.do_enter(True)

    def delete(self):
        frm, to = self.GetSelection()
        self.Remove(frm, to)
        self.do_enter(True)


    def DoFindNext(self, findData, findDlg=None):
        backward = not (findData.GetFlags() & wx.FR_DOWN)
        matchcase = (findData.GetFlags() & wx.FR_MATCHCASE) != 0
        end = self.GetLastPosition()
        textstring = self.GetRange(0, end)
        findstring = findData.GetFindString()
        if not matchcase:
            textstring = textstring.lower()
            findstring = findstring.lower()
        if backward:
            start = self.GetSelection()[0]
            loc = textstring.rfind(findstring, 0, start)
        else:
            start = self.GetSelection()[1]
            loc = textstring.find(findstring, start)

        # if it wasn't found then restart at begining
        if loc == -1: # and start != 0:
            if backward:
                start = end
                loc = textstring.rfind(findstring, 0, start)
            else:
                start = 0
                loc = textstring.find(findstring, start)

        # was it still not found?
        if loc == -1:
            dlg = wx.MessageDialog(self, 'Unable to find the search text.',
                          'Not found!',
                          wx.OK | wx.ICON_INFORMATION)
            dlg.ShowModal()
            dlg.Destroy()

        # show and select the found text
        self.ShowPosition(loc)
        self.SetSelection(loc, loc + len(findstring))

    def DoFindReplace(self, findData, findDlg=None):
        backward = not (findData.GetFlags() & wx.FR_DOWN)
        matchcase = (findData.GetFlags() & wx.FR_MATCHCASE) != 0
        end = self.GetLastPosition()
        textstring = self.GetRange(0, end)
        findstring = findData.GetFindString()
        if not matchcase:
            textstring = textstring.lower()
            findstring = findstring.lower()
        if backward:
            start = self.GetSelection()[0]
            loc = textstring.rfind(findstring, 0, start)
        else:
            start = self.GetSelection()[1]
            loc = textstring.find(findstring, start)
        replacestring = findData.GetReplaceString()
        # if it wasn't found then restart at begining
        if loc == -1: # and start != 0:
            if backward:
                start = end
                loc = textstring.rfind(findstring, 0, start)
            else:
                start = 0
                loc = textstring.find(findstring, start)

        # was it still not found?
        if loc == -1:
            dlg = wx.MessageDialog(self, 'Unable to find the search text.',
                          'Not found!',
                          wx.OK | wx.ICON_INFORMATION)
            dlg.ShowModal()
            dlg.Destroy()

        # replace
        self.push_undo_init()
        self.Remove(loc, loc + len(findstring))
        self.SetInsertionPoint(loc)
        self.push_undo_step()
        self.WriteText(replacestring)
        self.push_undo_step()
        self.push_undo_term()
        self.do_enter(True)
        self.ShowPosition(loc)

    def DoFindReplaceAll(self, findData, findDlg=None):
        backward = not (findData.GetFlags() & wx.FR_DOWN)
        matchcase = (findData.GetFlags() & wx.FR_MATCHCASE) != 0
        end = self.GetLastPosition()
        textstring = self.GetRange(0, end)
        findstring = findData.GetFindString()
        replacestring = findData.GetReplaceString()
        loc = 0
        self.push_undo_init()
        while True:
            loc = textstring.find(findstring, loc)
            if loc == -1:
                break
            self.Remove(loc, loc + len(findstring))
            self.SetInsertionPoint(loc)
            self.push_undo_step()
            self.WriteText(replacestring)
            self.push_undo_step()
            self.do_enter(True)
            loc += 1
        self.push_undo_term()
        self.ShowPosition(0)

    def char_event(self, e):
        self.doing_return = False
        key = e.GetKeyCode()
        c = e.GetUniChar()
        #print "c = ", c
        if c == ord('\r'):
            e.Skip()
            wx.PostEvent(self, IndentEvent(True, False))
            self.return_pressed = True
            return
        elif (c == ord('\t')):
            wx.PostEvent(self, IndentEvent(False, True))
            return
        elif c == 26:   # ^Z
            self.Undo()
            return
        elif c == 8:    # backspace
            wx.PostEvent(self, IndentEvent(False, True))           
        if key < 255:
            self.change = True
            wx.PostEvent(self, LayoutEvent())
        e.Skip()


    def on_quit(self):
        if self.IsModified():
            dlg = wx.MessageDialog(self, 'Save before exiting?', '', wx.YES_NO | wx.YES_DEFAULT | wx.CANCEL |  wx.ICON_QUESTION)
            val = dlg.ShowModal()
            if val == wx.ID_YES:
                self.save_file()
                self.Destroy()
                return True
            elif val == wx.ID_CANCEL:
                dlg.Destroy()
                return False
            else:
                self.Destroy()
                return True
        else:
            self.Destroy()
            return True


    def open_file(self, file):
        fd = open(file, "U")
        text = fd.read()
        fd.close()
        self.file = file
        #self.Clear()
        #self.AppendText(text)
        self.LoadFile(file)
        self.previous = self.GetValue()
        self.colour_text(text, 0, len(text), True)
        self.SetInsertionPoint(0)
        self.SetModified(False)
        self.saved_text = self.previous

    def save_file(self):
        try:
            fd = open(self.file, "w") 
            fd.write(self.GetValue())
            fd.close()
            self.SetModified(False)
            self.parent.SetTitle(self.file)
            self.saved_text = self.GetValue()
            return True
        except:
            return False

    def save_as_file(self, file):
        try:
            fd = open(file, "w") 
            fd.write(self.GetValue())
            fd.close()
            self.file = file
            self.SetModified(False)
            self.parent.SetTitle(self.file)
            self.saved_text = self.GetValue()
            return True
        except:
            return False


    def text_updated(self, e):
        if self.file:
            self.parent.SetTitle('*'+self.file+'*')
        else:
            self.parent.SetTitle('*Untitled*')

    def parse_next(self, text, start, rexps):
        res = [Matcher(key, retable[key].search(text, start), rexps) 
               for key in rexps]
        res.sort()
        return res[0]

    
    def colour_text(self, text, start, end, do_colour):
        #print start, end, do_colour
        if do_colour:
            self.SetStyle(start, end, wx.TextAttr(colText="black"))
        while start < end:
            next = self.parse_next(text, start, re_order)
            next_rematch = next.rematch
            if not  next_rematch:
                return
            type = next.type
            next_end = next_rematch.end()
            if type == 'clause_end':
                self.clause_ends.append(next_end)
            if do_colour:
                self.SetStyle(next_rematch.start(),next_end,
                                   wx.TextAttr(colText=colours[type]))
            start = next_end
    
    def only_nl(self, xs):
        for type,_ in xs:
            if type != '\n':
                return False
        return True

    def clause_punct(self, text, start, end):
        tokens = []
        while start < end:
            next = self.parse_next(text, start, all)
            if not next.rematch:
                return tokens
            type = next.type
            if type == 'clause_end':
                tokens = []
            elif type =='u_comment1':
                tokens.append(('/*', next.rematch.start()))
            elif type not in punct:
                pass
            elif type == ')':
                self.pop_to(tokens, '(')
            elif type == ']':
                self.pop_to(tokens, '[')
            elif type == '*/':
                self.pop_to(tokens, '/*')
            elif type == ':-':
                if self.only_nl(tokens):
                    tokens.append((type,0))
            else:
                col,_ = self.PositionToXY(next.rematch.start())
                tokens.append((type,col))
            start = next.rematch.end()
        return tokens

                
    def pop_to_clause_end(self, pos):
        while self.clause_ends:
            end = self.clause_ends[-1]
            if end > pos:
                self.clause_ends.pop()
            else:
                return end
        return 0
        

    def push_undo(self):
        self.push_undo_init()
        self.push_undo_step()
        self.push_undo_term()

    def push_undo_init(self):
        self.change = False
        self.undo_stack = []

    def push_undo_step(self):
        text = self.GetValue()
        prev = self.previous
        pos = self.GetInsertionPoint()
        kind, diff_first, insert_text = string_diff(text, prev)
        if kind == 0:
            return
        elif kind > 0:   #add
            self.undo_stack.append(('insert', diff_first, insert_text, pos))
        else:    # del
            self.undo_stack.append(('delete', diff_first, insert_text, pos))
        self.previous = text

    def push_undo_term(self):
        if self.undo_stack != []:
            text = self.GetValue()
            order_pos = len(self.undo)
            self.undo.append(self.undo_stack)
            self.undo_pos = len(self.undo_order)
            self.undo_order.append((1, order_pos))

    def enter(self, e):
        #self.push_undo()
        self.do_enter(True)

    def do_enter(self, do_colour):
        text = self.GetValue()
        pos = self.GetInsertionPoint()
        start = self.pop_to_clause_end(pos)
        self.colour_text(text, start, len(text), do_colour)

    def get_indent(self, line):
        text = self.GetLineText(line)
        strip_text = text.strip()
        return text.find(strip_text[0])

    def get_start_clause(self, pos):
        clause_ends_index = len(self.clause_ends)-1
        while clause_ends_index > 0:
            eoc_pos = self.clause_ends[clause_ends_index]
            if eoc_pos < pos:
                return eoc_pos
            clause_ends_index -= 1
        return 0

            
    def pop_to(self, xs, x):
        while xs:
            popped,_ = xs.pop()
            if x in popped:
                return



    def compute_indent(self, punct):
        indent1 = 0
        indent2 = 0
        save_indent = indent2
        size = len(punct)
        i = 0
        in_comment = False
        while i < size:
            type, col = punct[i]
            if type == ':-':
                indent1 = 4
                indent2 = 4
                save_indent = indent2
                in_comment = False
            elif type == '(':
                indent1 = col
                indent2 = col + 1
                save_indent = indent2
                in_comment = False
            elif type == ' (':
                indent1 = col
                indent2 = col + 2
                save_indent = indent2
                in_comment = False
            elif type == '[':
                indent1 = col
                indent2 = col + 1
                save_indent = indent2
                in_comment = False
            elif type == '/*':
                indent1 = col
                indent2 = col + 1
                save_indent = indent2
                in_comment = True
            elif in_comment:
                indent2 = save_indent
            elif type == '\n' and \
                    not (i > 0 and \
                             punct[i-1][0] in [',', ' (', '->', ';']):
                indent2 = indent1
            elif type in ['->', ';']:
                in_comment = False
                indent2 = save_indent
            i += 1
        return indent2
                

            


    def do_indent(self, e):
        #print "doing indent"
        text = self.GetValue()
        return_pressed = e.return_pressed
        pos = self.GetInsertionPoint()
        if return_pressed:
            self.do_enter(False)
        col,line = self.PositionToXY(pos)
        line_start_pos = self.XYToPosition(0,line)
        if  line_start_pos == -1:
             line_start_pos = pos
        start_clause_pos = self.get_start_clause(line_start_pos)
        punct = self.clause_punct(text, start_clause_pos, line_start_pos)
        indent = self.compute_indent(punct)
        line_text = self.GetLineText(line)
        curr_indent = len(line_text) - len(line_text.lstrip())
        if indent > curr_indent:
            self.SetInsertionPoint(line_start_pos)
            self.WriteText((indent - curr_indent)*' ')
            if pos < line_start_pos + indent:
                self.SetInsertionPoint(line_start_pos + indent)
            else:
                self.SetInsertionPoint(pos + indent - curr_indent)
        elif indent < curr_indent:
            self.SetInsertionPoint(line_start_pos)
            self.Remove(line_start_pos, 
                             line_start_pos + (curr_indent - indent)) 
            if pos < line_start_pos + curr_indent:
                self.SetInsertionPoint(line_start_pos + indent)
            else:
                self.SetInsertionPoint(pos + indent - curr_indent)
        if e.do_colour:        
            text = self.GetValue()
            start = self.pop_to_clause_end(pos)
            self.colour_text(text, start, len(text), True)
        self.push_undo()
        #print '----- push_undo ------', self.undo,self.undo_order,self.undo_pos



class EditorFrame(wx.Frame):
    #FILEMENU_OPEN = wx.NewId()
    #FILEMENU_NEW = wx.NewId()
    #EDITMENU_UNDO = wx.NewId()
    #new_bmp =  None
    #open_bmp = None
    #copy_bmp = None
    #paste_bmp= None
    #undo_bmp= None

    menu_data = \
        [
        ('&File', 
         [("New", 'new_bmp', 'new_window'),
          ("Open", 'open_bmp', 'open_file'),
          ('', '', ''),
          ("Save", 'save_bmp', 'save_file'),
          ("Save As", 'save_as_bmp', 'save_as_file'),
          ('', '', ''),
          ("Close", 'close_bmp', 'OnQuit')
          ]
         ),
        ("&Edit", 
         [("Undo\tCtrl-z", 'undo_bmp', 'undo_cmd'),
          ('', '', ''),
          ("Cut\tCtrl-x", 'cut_bmp', 'OnCut'),
          ("Copy\tCtrl-c", 'copy_bmp', 'OnCopy'),
          ("Paste\tCtrl-v", 'paste_bmp', 'OnPaste'),
          ("Delete", 'delete_bmp', 'OnDelete'),
          ('', '', ''),
          ("Select All\tCtrl-a", '', 'OnSelectAll')
          ]
         ),
        ("&Search",
         [("Find\tCtrl-f", 'find_bmp', 'OnFindDialog'),
          ("Replace\tCtrl-h", 'replace_bmp', 'OnReplaceDialog')
          ]
         ),
        ("Help",
         [("&About this application", "", "OnAbout")
          ]
         )
        ]
    
    def create_menus(self):
        menuBar = wx.MenuBar()
        self.SetMenuBar(menuBar)
        for menu_name, items in self.menu_data:
            menu = wx.Menu()
            menuBar.Append(menu, menu_name)
            for name, image, cmd in  items:
                if name:
                    id = wx.NewId()
                    item = wx.MenuItem(menu, id, name)
                    if image:
                        item.SetBitmap(eval('self.'+image))
                    menu.AppendItem(item)
                    self.Bind(wx.EVT_MENU, eval('self.'+cmd), id=id)
                else:
                    menu.AppendSeparator()

    def __init__(self, parent, id):
        wx.Frame.__init__(self, parent, id, 'Untitled', size=(60,40))
        font = wx.Font(font_size, wx.MODERN, wx.NORMAL, wx.NORMAL)
        self.SetFont(font)
        width,height =  self.GetTextExtent(80*'a')
        self.SetSize((width,height*30))
        self.create_menus()
        self.ctrl = EditorWindow(self)
        box = wx.BoxSizer(wx.VERTICAL)
        box.Add(self.ctrl, 1, wx.ALL|wx.GROW, 1)
        self.SetSizer(box)
        self.SetAutoLayout(True)
        self.file = None
        self.Bind(wx.EVT_CLOSE, self.OnQuit)
        self.Bind(wx.EVT_FIND, self.OnFindNext)
        self.Bind(wx.EVT_FIND_NEXT, self.OnFindNext)
        self.Bind(wx.EVT_FIND_CLOSE, self.OnFindClose)
        self.Bind(wx.EVT_FIND_REPLACE, self.OnFindReplace)
        self.Bind(wx.EVT_FIND_REPLACE_ALL, self.OnFindReplaceAll)
        self.findData = wx.FindReplaceData()
        self.findData.SetFlags(wx.FR_DOWN)
        self.findDlg = None

    def OnQuit(self, e):
        if self.ctrl.on_quit():
            self.Destroy()

    def OnCut(self, e):
        self.ctrl.Cut()

    def OnCopy(self, e):
        self.ctrl.Copy()

    def OnPaste(self, e):
        self.ctrl.Paste()

    def OnDelete(self, e):
        self.ctrl.Delete()

    def OnSelectAll(self, e):
        self.ctrl.SelectAll()

    def OnAbout(self, e):
        d= wx.MessageDialog(self, "Simple Prolog Editor\nAuthor: Peter Robinson\nEmail: pjr@itee.uq.edu.au\nCopyright (c) 2010 Peter Robinson","About PrologEditor", wx.OK) 
        d.ShowModal()
        d.Destroy() 


    def OnFindDialog(self, e):  
        if self.findDlg is not None:
            return
        self.findDlg = wx.FindReplaceDialog(self, self.findData, "Find")
        self.findDlg.Show()


    def OnReplaceDialog(self, e):
        self.findDlg = wx.FindReplaceDialog(self, self.findData, 
                                            "Find & Replace",
                                            wx.FR_REPLACEDIALOG)
        self.findDlg.Show()


    def OnFindClose(self, event):
        self.findDlg.Destroy()
        self.findDlg = None
    

    def OnFindNext(self, event):
        self.ctrl.DoFindNext(self.findData, self.findDlg)
        #if self.findDlg is not None:
        #    self.OnFindClose(None)


    def OnFindReplace(self, e):
        self.ctrl.DoFindReplace(self.findData, self.findDlg)
    def OnFindReplaceAll(self, e):
        self.ctrl.DoFindReplaceAll(self.findData, self.findDlg)


    def undo_cmd(self, e):
        self.ctrl.Undo()

    def open_file(self, e):
        fc = wx.FileDialog(self, defaultFile="", defaultDir=os.getcwd(),
                           message="open")
        if fc.ShowModal() == wx.ID_OK:
            self.open_a_file(fc)

        
    def open_a_file(self, fc): 
        if self.ctrl.file or self.ctrl.IsModified():
            frame = self.new_window(None)
            frame.open_a_file(fc)
        else:
            self.ctrl.open_file(fc.GetPath())
            self.SetTitle(fc.GetPath())
            os.chdir(os.path.split(fc.GetPath())[0])
            
    def save_file(self, e):
        if self.ctrl.file:
            result = self.ctrl.save_file()
            if not result:
                dlg = wx.MessageDialog(self, "Couldn't save file",
                                       'File Error',
                                       wx.OK | wx.ICON_ERROR
                                       )
                dlg.ShowModal()
                dlg.Destroy()
        else:
            self.save_as_file(e)

    def save_as_file(self, e):
        dlg = wx.FileDialog(self, "Save As", defaultDir=os.getcwd(), 
                            defaultFile="", wildcard=wildcard, 
                            style=wx.SAVE)
        if dlg.ShowModal() == wx.ID_OK:
            filename=dlg.GetFilename()
            dirname=dlg.GetDirectory()
            os.chdir(dirname)
            if not self.ctrl.save_as_file(filename):
                dlg = wx.MessageDialog(self, "Couldn't save file as",
                                       'File Error',
                                       wx.OK | wx.ICON_ERROR
                                       )
        dlg.Destroy()

    def new_window(self, e):
        frame = EditorFrame(parent=None, id=-1)
        frame.Show()
        return frame

if  __name__ == '__main__':
    app = wx.PySimpleApp()

    bpm_size = (16,16)

    EditorFrame.new_bmp =  wx.ArtProvider.GetBitmap(wx.ART_NEW, wx.ART_TOOLBAR, bpm_size)
    EditorFrame.open_bmp = wx.ArtProvider.GetBitmap(wx.ART_FILE_OPEN, wx.ART_TOOLBAR, bpm_size)
    EditorFrame.copy_bmp = wx.ArtProvider.GetBitmap(wx.ART_COPY, wx.ART_TOOLBAR, bpm_size)
    EditorFrame.paste_bmp= wx.ArtProvider.GetBitmap(wx.ART_PASTE, wx.ART_TOOLBAR, bpm_size)
    EditorFrame.undo_bmp= wx.ArtProvider.GetBitmap(wx.ART_UNDO, wx.ART_TOOLBAR, bpm_size)
    EditorFrame.close_bmp= wx.ArtProvider.GetBitmap(wx.ART_QUIT, wx.ART_TOOLBAR, bpm_size)
    EditorFrame.save_bmp= wx.ArtProvider.GetBitmap(wx.ART_FILE_SAVE, wx.ART_TOOLBAR, bpm_size)
    EditorFrame.save_as_bmp= wx.ArtProvider.GetBitmap(wx.ART_FILE_SAVE_AS, wx.ART_TOOLBAR, bpm_size)
    EditorFrame.cut_bmp= wx.ArtProvider.GetBitmap(wx.ART_CUT, wx.ART_TOOLBAR, bpm_size)
    EditorFrame.copy_bmp= wx.ArtProvider.GetBitmap(wx.ART_COPY, wx.ART_TOOLBAR, bpm_size)
    EditorFrame.paste_bmp= wx.ArtProvider.GetBitmap(wx.ART_PASTE, wx.ART_TOOLBAR, bpm_size)
    EditorFrame.delete_bmp= wx.ArtProvider.GetBitmap(wx.ART_DELETE, wx.ART_TOOLBAR, bpm_size)
    EditorFrame.find_bmp= wx.ArtProvider.GetBitmap(wx.ART_FIND, wx.ART_TOOLBAR, bpm_size)
    EditorFrame.replace_bmp= wx.ArtProvider.GetBitmap(wx.ART_FIND_AND_REPLACE, wx.ART_TOOLBAR, bpm_size)

    frame = EditorFrame(parent=None, id=-1)
    frame.Show()
    app.MainLoop()
    

