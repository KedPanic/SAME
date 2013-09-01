//===========================================
// Copyright (C) 2013 Cedric Liaudet
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
// of the Software, and to permit persons to whom the Software is furnished to
// do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
// PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
// HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
// OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//===========================================
#ifndef __CONFIG__
#define __CONFIG__

#include <SamCommon.h>
#include <SamNetwork.h>

static const uint16 SERVER_PORT = 54321;
static const uint16 CLIENT_PORT = 12345;

static const uint16 CLIENT_MAX_SIZE_NAME = 64;
static const uint16 CLIENT_MAX_SIZE_MESSAGE = 1330;

// list of command
static const char CMD_LOGIN			= 0x01;
static const char CMD_LOGOUT		= 0x02;
static const char CMD_MSG			= 0x03;

static const char CMD_SERVER_LOGIN  = 0x11;
static const char CMD_SERVER_LOGOUT = 0x12;
static const char CMD_SERVER_MSG    = 0x13;

#endif // __CONFIG__
