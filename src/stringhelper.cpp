/*
 * Copyright 2003-2005 The Apache Software Foundation.
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

#include <log4cxx/helpers/stringhelper.h>
#include <log4cxx/helpers/transcoder.h>
#include <algorithm>
#include <vector>
#include <locale>
#include <apr_strings.h>
#include <log4cxx/helpers/pool.h>

#define INT64_C(x) x##LL

using namespace log4cxx;
using namespace log4cxx::helpers;

std::string StringHelper::toLowerCase(const std::string& s)
{
        std::string d;
        std::transform(s.begin(), s.end(),
                std::insert_iterator<std::string>(d, d.begin()), tolower);
        return d;
}

std::wstring StringHelper::toLowerCase(const std::wstring& s)
{
        std::wstring d;
#if defined(_MSC_VER)
        std::transform(s.begin(), s.end(),
                std::insert_iterator<std::wstring>(d, d.begin()),
                towlower);
#else
        std::transform(s.begin(), s.end(),
                std::insert_iterator<std::wstring>(d, d.begin()),
                (int(*)(int)) std::tolower);
#endif
        return d;
}

std::string StringHelper::trim(const std::string& s)
{
        std::string::size_type pos = s.find_first_not_of(' ');
        if (pos == std::string::npos)
        {
                return std::string();
        }

        std::string::size_type n = s.find_last_not_of(' ') - pos + 1;
        return s.substr(pos, n);
}

std::wstring StringHelper::trim(const std::wstring& s)
{
        std::wstring::size_type pos = s.find_first_not_of(L' ');
        if (pos == std::wstring::npos)
        {
                return std::wstring();
        }

        std::wstring::size_type n = s.find_last_not_of(L' ') - pos + 1;
        return s.substr(pos, n);
}


bool StringHelper::startsWith(const std::wstring& teststr, const std::wstring& substr)
    {
    bool val = false;
    if(teststr.length() > substr.length()) {
        val = teststr.substr(0, substr.length()) == substr;
    }

    return val;
}

bool StringHelper::startsWith(const std::string& teststr, const std::string& substr)
    {
    bool val = false;
    if(teststr.length() > substr.length()) {
        val = teststr.substr(0, substr.length()) == substr;
    }

    return val;
}


bool StringHelper::endsWith(const std::string& s, const std::string& suffix)
{
    if (suffix.length() <= s.length()) {
      return suffix.compare(s.length() - suffix.length(), suffix.length(), s) == 0;
    }
    return false;
}


bool StringHelper::endsWith(const std::wstring& s, const std::wstring& suffix)
{
    if (suffix.length() <= s.length()) {
      return suffix.compare(s.length() - suffix.length(), suffix.length(), s) == 0;
    }
    return false;
}

bool StringHelper::equalsIgnoreCase(const std::string& s1, const char* upper, const char* lower) {
  for (std::string::const_iterator iter = s1.begin();
       iter != s1.end();
       iter++, upper++, lower++) {
       if (*iter != *upper && *iter != * lower) return false;
  }
  return (*upper == 0);
}

bool StringHelper::equalsIgnoreCase(const std::wstring& s1, const wchar_t* upper, const wchar_t* lower) {
  for (std::wstring::const_iterator iter = s1.begin();
       iter != s1.end();
       iter++, upper++, lower++) {
       if (*iter != *upper && *iter != * lower) return false;
  }
  return (*upper == 0);
}

bool StringHelper::getline(std::string& in, std::string& line) {
  if (in.empty()) {
    return false;
  }
  size_t nl = in.find('\n');
  if (nl == std::string::npos) {
    line = in;
    in.erase(in.begin(), in.end());
  } else {
    line.assign(in, 0, nl);
    in.erase(in.begin(), in.begin() + nl + 1);
  }
  return true;
}


bool StringHelper::getline(std::wstring& in, std::wstring& line) {
  if (in.empty()) {
    return false;
  }
  size_t nl = in.find(L'\n');
  if (nl == std::wstring::npos) {
    line = in;
    in.erase(in.begin(), in.end());
  } else {
    line.assign(in, 0, nl);
    in.erase(in.begin(), in.begin() + nl + 1);
  }
  return true;
}

int StringHelper::toInt(const std::string& s) {
  return atoi(s.c_str());
}

int StringHelper::toInt(const std::wstring& s) {
  LOG4CXX_DECODE_WCHAR(logstr, s);
  LOG4CXX_ENCODE_CHAR(charstr, logstr);
  return atoi(charstr.c_str());
}

log4cxx_int64_t StringHelper::toInt64(const std::string& s) {
  return apr_atoi64(s.c_str());
}

log4cxx_int64_t StringHelper::toInt64(const std::wstring& s) {
  LOG4CXX_DECODE_WCHAR(logstr, s);
  LOG4CXX_ENCODE_CHAR(charstr, logstr);
  return apr_atoi64(charstr.c_str());
}

LogString StringHelper::toString(int n, Pool& pool) {
  char* fmt = apr_itoa((apr_pool_t*) pool.getAPRPool(), n);
  LogString str;
  log4cxx::helpers::Transcoder::decode(fmt, strlen(fmt), str);
  return str;
}

void StringHelper::toString(int n, Pool& pool, std::string& str) {
  char* fmt = apr_itoa((apr_pool_t*) pool.getAPRPool(), n);
  str.append(fmt);
}

void StringHelper::toString(int n, Pool& pool, std::wstring& str) {
  char* fmt = apr_itoa((apr_pool_t*) pool.getAPRPool(), n);
  log4cxx::helpers::Transcoder::decode(fmt, strlen(fmt), str);
}



LogString StringHelper::toString(log4cxx_int64_t n, Pool& pool) {
  std::string s;
  toString(n, pool, s);
  LogString rv;
  Transcoder::decode(s, rv);
  return rv;
}

void StringHelper::toString(log4cxx_int64_t n, Pool& pool, std::string& s) {
  if (n >= INT_MIN && n <= INT_MAX) {
    s.append(apr_itoa((apr_pool_t*) pool.getAPRPool(), (int) n));
  } else {
    const log4cxx_int64_t BILLION = APR_INT64_C(1000000000);
    int billions = (int) (n / BILLION);
    s.append(apr_itoa((apr_pool_t*) pool.getAPRPool(), billions));
    int remain = (n - billions * BILLION);
    if (remain < 0) remain *= -1;
    char* lower = apr_itoa((apr_pool_t*) pool.getAPRPool(), remain);
    int fill = 9 - strlen(lower);
    s.append(fill, LOG4CXX_STR('0'));
    s.append(lower);
  }
}

void StringHelper::toString(log4cxx_int64_t n, Pool& pool, std::wstring& ws) {
    std::string s;
    toString(n, pool, s);
    LogString ls;
    Transcoder::decode(s, ls);
    Transcoder::encode(ls, ws);
}

LogString StringHelper::toString(size_t n, Pool& pool) {
  return toString((log4cxx_int64_t) n, pool);
}

void StringHelper::toString(size_t n, Pool& pool, std::string& s) {
  toString((log4cxx_int64_t) n, pool, s);
}

void StringHelper::toString(size_t n, Pool& pool, std::wstring& ws) {
  toString((log4cxx_int64_t) n, pool, ws);
}



LogString StringHelper::formatHex(const void* ptr) {
    const logchar* hexdigits = LOG4CXX_STR("0123456789ABCDEF");
    apr_int64_t iptr = (apr_int64_t) ptr;
    int width = sizeof(ptr)*2 + 2;
    LogString s(width, LOG4CXX_STR('x'));
    s[0] = LOG4CXX_STR('0');
    for(int i = width - 1; i >= 2; i--) {
      s[i] = hexdigits[iptr % 0x0F];
      iptr = iptr >> 4;
    }
    return s;
}
