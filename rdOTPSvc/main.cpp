#include "pch.h"
#include "ServiceMain.h"

#include "ETWTraceManager.h"

#include <stdio.h>

int main(int argc, char** argv)
{
	if (argc == 2)
	{
		if (!strcmp(argv[1], "/install"))
		{
			// install service
			ServiceMain::InstallService();
		}
		else if (!strcmp(argv[1], "/uninstall"))
		{
			// remove service
			ServiceMain::RemoveService();
		}
	}
	else
	{
		ServiceMain::RunService();
	}

	return 0;
}