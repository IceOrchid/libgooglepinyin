/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdlib.h>
#include <stdio.h>
#include "pinyinime.h"
#include <cassert>
#include <memory.h>

#ifdef WIN32
#include <Windows.h>
#include <tchar.h>
#endif

#include <locale.h>

using namespace ime_pinyin;

int main(int argc, char* argv[])
{
  setlocale(LC_ALL, "");
  char* szSysDict = "../build/data/dict_pinyin.dat";
  char* szUserDict = "";
  if (argc >= 3) {
    szSysDict = argv[1];
    szUserDict = argv[2];
  }

  bool ret = im_open_decoder(szSysDict, szUserDict);  // ����
  assert(ret);
  im_set_max_lens(32, 16);
  char szLine[256];

  while (true) {
    printf("\n >");
#ifdef WIN32
    gets_s(szLine, 256);
#else
    gets(szLine);
#endif
    if (strlen(szLine) == 0)
      break;
    
    im_reset_search();
    size_t nr = im_search(szLine, strlen(szLine)); // ��ѯ
    size_t size = 0;
    printf("%s\n", im_get_sps_str(&size));  // ��ȡ��ѯ�������
    char16 str[64] = { 0 };
    for (auto i = 0; i < nr; i++)
    {
      im_get_candidate(i, str, 32);         // ��ȡ��ѯ��ѡ
#ifdef WIN32
      const wchar_t* szCand = (const wchar_t*)str;
      wprintf(L"%s\n", szCand);
#else
#endif
      int j = 0;
      j++;
    }
  }

  im_close_decoder();                 // �ر�

	return 0;
}
