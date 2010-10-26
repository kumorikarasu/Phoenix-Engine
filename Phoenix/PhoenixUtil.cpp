#include "PhoenixUtil.h"

//TODO: Vertex2 Class Operator Overloading
namespace PhoenixCore{

void ExtensionFromFilename(TCHAR *szFileName, TCHAR *szExtension)
{
	int len = _tcslen(szFileName);
  int begin;

	for (begin=len;begin>=0;begin--) {
		if (szFileName[begin] == '.') {
			begin++;
			break;
		}
	}

	if (begin <= 0) {
		szExtension[0] = '\0';
	}
	else {
		_tcscpy(szExtension, &szFileName[begin]);
	}
}
}