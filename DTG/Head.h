#pragma once
#pragma once
#ifdef _DEBUG
# ifdef _UNICODE
#	pragma comment(lib,"DuiLib_ud.lib")
#	else
#pragma comment(lib,"DuiLib_d.lib")
# endif
#else
# ifdef _UNICODE
#pragma comment (lib , "DuiLib_ud.lib")
#	else
#pragma comment(lib,"DuiLib_d.lib")
# endif
#endif
#include "UIlib.h"
using namespace DuiLib;
