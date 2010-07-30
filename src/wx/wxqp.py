import subprocess,sys,threading

import wx,re

if wx.Platform == '__WXMSW__':
    face = 'Courier New'
    font_size = 10
else:
    face = 'Courier'
    font_size = 10

EVT_STDOUT_ID = wx.NewId()


class StdoutEvent(wx.PyEvent):
    """Simple event to carry arbitrary result data."""
    def __init__(self, data):
        """Init Result Event."""
        wx.PyEvent.__init__(self)
        self.SetEventType(EVT_STDOUT_ID)
        self.data = data

proc = subprocess.Popen('qp',
                        shell=True, stdin=subprocess.PIPE,
                        stdout=subprocess.PIPE,
                        stderr=subprocess.STDOUT, #universal_newlines=True,
                        bufsize=0)

class EditorFrame(wx.Frame):
    def __init__(self, parent, id):
        wx.Frame.__init__(self, parent, id, 'Editor')
        self.ctrl = wx.TextCtrl(self, style=wx.TE_MULTILINE)
        font = wx.Font(font_size, wx.MODERN, wx.NORMAL, wx.NORMAL)
        self.ctrl.SetFont(font)
        width,height =  self.ctrl.GetTextExtent(80*'a')
        self.SetSize((width,height*30))
        print 'aaa'
        qp_thread = threading.Thread(target=self.read_qp)
        qp_thread.setDaemon(1)
        qp_thread.start()
        print 'bbb'
        self.ctrl.Bind(wx.EVT_CHAR, self.char_event, self.ctrl)
        self.ctrl.Bind(wx.EVT_CLOSE, self.close_event, self.ctrl)
        self.ctrl.Connect(-1, -1, EVT_STDOUT_ID, self.do_stdout)
        self.position = self.ctrl.GetInsertionPoint()

    def char_event(self, event):
        keycode = event.GetKeyCode()
        if keycode == wx.WXK_RETURN:
            pos = self.ctrl.GetInsertionPoint()
            _col,line = self.ctrl.PositionToXY(pos)
            col,_line = self.ctrl.PositionToXY(self.position)
            line_text = self.ctrl.GetLineText(line)
            line_text = line_text[col:]
            if line_text.startswith('| ?- '):
                line_text = line_text[5:]
            proc.stdin.write(line_text+'\n')
            proc.stdin.flush()
            self.ctrl.WriteText('\n')
        else:
            event.Skip()

    def do_stdout(self, event):
        self.ctrl.WriteText(event.data)
        self.position = self.ctrl.GetInsertionPoint()

    def read_qp(self):
        while True:
            proc_read = proc.stdout.read(1)
            wx.PostEvent(self.ctrl, StdoutEvent(proc_read))

    def close_event(self, e):
        print 'closing'
        proc.kill()

if  __name__ == '__main__':
    app = wx.PySimpleApp()
    frame = EditorFrame(parent=None, id=-1)
    frame.Show()
    app.MainLoop()
    







