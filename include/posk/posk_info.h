#define KERNEL_NAME         "posk"
#define KERNEL_VERSION      "0.0-zed"
#define KERNEL_VERSION_NAME "Core Dump"
#define KERNEL_COPYRIGHT    "gpl"
#define KERNEL_AUTHORS      "Pat McDonnell, Paul Tagliamonte"
#define KERNEL_YEAR         "2009 - 2010"

#include <posk/posk_stdout.h>

void copyright() {
	printf( "Running %s, v%s: '%s'\n", KERNEL_NAME, KERNEL_VERSION, KERNEL_VERSION_NAME );
	printf( "Copyright (c) %s, %s.\nI'm licenced under the %s\n", KERNEL_AUTHORS, KERNEL_YEAR, KERNEL_COPYRIGHT  );
}
