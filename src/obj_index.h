// obj_index.h - Object for handling a .qo file during linking.
//
// ##Copyright##
// 
// Copyright (C) 2000-2004
// School of Information Technology and Electrical Engineering
// The University of Queensland
// Australia 4072
// 
// email: pjr@itee.uq.edu.au
// 
// The Qu-Prolog System and Documentation  
// 
// COPYRIGHT NOTICE, LICENCE AND DISCLAIMER.
// 
// Copyright 2000-2004 by The University of Queensland, 
// Queensland 4072 Australia
// 
// Permission to use, copy and distribute this software and associated
// documentation for any non-commercial purpose and without fee is hereby 
// granted, subject to the following conditions:
// 
// 1. 	that the above copyright notice and this permission notice and 
// 	warranty disclaimer appear in all copies and in supporting 
// 	documentation; 
// 
// 2.	that the name of the University of Queensland not be used in 
// 	advertising or publicity pertaining to distribution of the software 
// 	without specific, written prior permission; 
// 
// 3.	that users of this software should be responsible for determining the 
// 	fitness of the software for the purposes for which the software is 
// 	employed by them; 
// 
// 4. 	that no changes to the system or documentation are subsequently 
// 	made available to third parties or redistributed without prior 
// 	written consent from the ITEE; and
// 
// The University of Queensland disclaims all warranties with regard to this
// software, including all implied warranties of merchantability and fitness
// to the extent permitted by law. In no event shall the University of 
// Queensland be liable for any special, indirect or consequential damages or 
// any damages whatsoever resulting from loss of use, data or profits, whether 
// in an action of contract, negligence or other tortious action, arising out 
// of or in connection with the use or performance of this software.
// 
// THE UNIVERSITY OF QUEENSLAND MAKES NO REPRESENTATIONS ABOUT THE ACCURACY OR
// SUITABILITY OF THIS MATERIAL FOR ANY PURPOSE.  IT IS PROVIDED "AS IS",
// WITHOUT ANY EXPRESSED OR IMPLIED WARRANTIES.
// 
// 
// For information on commercial use of this software contact ITEE.
// 
// ##Copyright##
//
// $Id: obj_index.h,v 1.3 2002/06/30 05:30:00 qp Exp $

//
// Format of a .qo file
// --------------------
//
//	+-------+
//	| size	|	} SIZE_OF_ADDRESS
//	+-------+
//	|   s	|	} ignore 1st byte
//	|   t	|	}
//	|   r	|	} size bytes
//	|   i	|	}
//	|   n	|	}
//	|   g	|	}
//	|   s	|	}
//	+-------+
//	| size	|	} SIZE_OF_ADDRESS
//	+-------+
//	|   n	|	} ignore 1st byte ???????
//	|   u	|	}
//	|   m	|	} size bytes
//	|   b	|	}
//	|   e	|	}
//	|   r	|	}
//	|   s	|	}
//	+-------+
//	| size	|	} SIZE_OF_OFFSET
//	+-------+
//	| q  c	|	}
//	| u  o	|	}
//	| e  d	|	} size bytes
//	| r  e	|	}
//	| y	|	}
//	+-------+
//	|string#|	} SIZE_OF_ADDRESS	}
//	+-------+				}
//	| arity	|	} SIZE_OF_NUMBER	}
//	+-------+				}
//	| size	|	} SIZE_OF_OFFSET	} repeat for each predicate
//	+-------+				}
//	|  c	|	}			}
//	|  o	|	} size bytes		}
//	|  d	|	}			}
//	|  e	|	}			}
//	+-------+
//

#ifndef	OBJ_INDEX_H
#define	OBJ_INDEX_H

#include "atom_table.h"
#include "objects.h"
#include "pred_table.h"
#include "string_map.h"

class	ObjectIndex
{

private:

  Code& code;
  AtomTable& atoms;
  PredTab& predicates;

  const char *name;		// file name
  StringMapLoc stringMap;	// string map location before reading

  bool query;			// True if object file had query code
  AtomLoc queryName;		// Name of the query code

  CodeLoc codeAreaBase;	// code location before reading
  CodeLoc codeAreaTop;	// code location after reading

public:

  ObjectIndex(Code& c, AtomTable& a, PredTab& p) 
    : code(c), atoms(a), predicates(p), query(false) { }

  //
  // Load a .qo file into the memory and record the boundaries of
  // string map, number map, query, and code areas.
  // Return whether it is successful or not.
  //
  bool	loadObjectFile(const char *file, word32& NumQuery,
		       StringMap& string_map,
		       PredTab& predicates);

  //
  // Resolve the references to atoms and predicates in each object file.
  //
  void	resolveObject(const StringMap& string_map, 
		      PredTab& predicates, bool dump_query_calls,
		      Object*& query_name);
};

#endif	// OBJ_INDEX_H
