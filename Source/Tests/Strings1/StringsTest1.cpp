/*****************************************************************
|
|      Stings Test Program 1
|
|      (c) 2001-2003 Gilles Boccon-Gibod
|      Author: Gilles Boccon-Gibod (bok@bok.net)
|
 ****************************************************************/

/*----------------------------------------------------------------------
|       includes
+---------------------------------------------------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Neptune.h"

/*----------------------------------------------------------------------
|       Fail
+---------------------------------------------------------------------*/
static void
Fail()
{
    printf("##################################\n");
    //exit(1);
}

/*----------------------------------------------------------------------
|       CompareTest
+---------------------------------------------------------------------*/
static void
CompareTest(const char* name, const char* a, const char* b, int result, int expected)
{
    printf("%s %s %s = %d [%s]\n", a, name, b, result, result == expected ? "pass" : "fail");
    if (result != expected) Fail();
}

/*----------------------------------------------------------------------
|       EqualTest
+---------------------------------------------------------------------*/
static void
EqualTest(const char* name, const char* a, const char* b, const char* expected)
{
    printf("op %s on %s, result = %s ", name, a, b);
    if (strcmp(expected, b)) {
        printf(" [fail: exptected %s, got %s]\n", expected, b);
    } else {
        printf(" [pass]\n");
    }
    if (strcmp(expected, b)) Fail();
}

/*----------------------------------------------------------------------
|       StringTest
+---------------------------------------------------------------------*/
static void
StringTest(const char* name, const char* a, const char* expected)
{
    printf("%s: %s", name, a);
    if (strcmp(expected, a)) {
        printf(" [fail: exptected %s, got %s]\n", expected, a);
    } else {
        printf(" [pass]\n");
    }
    if (strcmp(expected, a)) Fail();
}

/*----------------------------------------------------------------------
|       IntTest
+---------------------------------------------------------------------*/
static void
IntTest(const char* name, int a, int expected)
{
    printf("%s: %d", name, a);
    if (a != expected) {
        printf(" [fail: exptected %d, got %d]\n", expected, a);
    } else {
        printf(" [pass]\n");
    }
    if (a != expected) Fail();
}

/*----------------------------------------------------------------------
|       main
+---------------------------------------------------------------------*/
int
main(int /*argc*/, char** /*argv*/)
{
    printf(":: testing empty string\n");
    NPT_String s;
    printf("sizeof(s)=%d, chars = '%s'\n", sizeof(s), s.GetChars());

    printf(":: testing allocation, new and delete\n");
    NPT_String* n0 = new NPT_String("Hello");
    delete n0;
    NPT_String n1 = "Bye";
    n1 = "ByeBye";

    printf(":: testing factories\n");
    NPT_String f0 = NPT_String::FromInteger(0);
    StringTest("FromInteger(0)", f0, "0");
    f0 = NPT_String::FromInteger(1234567);
    StringTest("FromInteger(1234567)", f0, "1234567");
    f0 = NPT_String::FromInteger(-1234567);
    StringTest("FromInteger(-1234567)", f0, "-1234567");

    printf(":: testing constructors\n");
    NPT_String s00;
    StringTest("constructor()", s00, "");
    NPT_String s01("abcdef");
    StringTest("constructor(const char*)", s01, "abcdef");
    NPT_String s02(s01);
    StringTest("constructor(const NPT_String&)", s02, "abcdef");
    NPT_String s03("abcdefgh", 3);
    StringTest("constructor(const char* s, unsigned int)", s03, "abc");
    NPT_String s04('Z');
    StringTest("constructor(char)", s04, "Z");
    NPT_String s05('Z', 7);
    StringTest("constructor(char, unsigned int)", s05, "ZZZZZZZ");
    NPT_String s06((const char*)NULL);
    StringTest("constructor(NULL)", s06, "");
    NPT_String s07(s06);
    StringTest("constructor(const NPT_String& = empty)", s07, "");
    NPT_String s08("");
    StringTest("constructor(const char* = \"\")", s08, "");
    NPT_String s09("jkhlkjh\0fgsdfg\0fgsdfg", 0, 10);
    StringTest("NPT_String s09(\"jkhlkjh\0fgsdfg\0fgsdfg\", 0, 10)", s09, "jkhlkjh");
        
    printf(":: testing assignments\n");
    NPT_String a00 = (const char*)NULL;
    StringTest("operator=(const char* = NULL)", a00, "");
    NPT_String a01 = a00;
    StringTest("operator=(const NPT_String& = empty)", a01, "");
    NPT_String a02 = "ab";
    StringTest("operator=(const char*)", a02, "ab");
    a02 = "abc";
    StringTest("operator=(const char* = bigger string)", a02, "abc");
    a02 = "ab";
    StringTest("operator=(const char* = smaller)", a02, "ab");
    a02 = (const char*)NULL;
    StringTest("operator=(const char* = NULL)", a02, "");
    a02 = "abcd";
    NPT_String a03 = a02;
    a02 = "ab";
    StringTest("operator=(const char*) with shared buffer", a02, "ab");
    a02 = "";
    StringTest("operator=(const char* = \"\")", a02, "");
    NPT_String p2("self");
    p2 = p2;
    StringTest("self assignment", p2, "self");
    NPT_String p3 = p2;
    p2 = p2;
    StringTest("self assignment with other ref", p2, "self");

    printf(":: testing casts\n");
    s = "hello";
    printf(":: cast to char*\n");
    StringTest("cast to char*", (char*)s, "hello");
    StringTest("cast to const char*", (const char*)s, "hello");
    
    printf(":: testing GetLength\n");
    NPT_String gl0 = "abcefg";
    IntTest("GetLength", gl0.GetLength(), 6);
    gl0 = "";
    IntTest("GetLength", gl0.GetLength(), 0);
    gl0 = "abcd";
    NPT_String gl1 = gl0;
    IntTest("GetLength", gl1.GetLength(), 4);
    gl1 += 'd';
    IntTest("GetLength", gl1.GetLength(), 5);

    printf("::testing references\n");
    NPT_String* d1;
    NPT_String d2;
    NPT_String d3;
    d1 = new NPT_String("first ref");
    d2 = *d1;
    delete d1;
    d1 = NULL;
    printf(d2);
    d3 = d2;
    d3 = "d3";
    printf(d2);
    printf(d3);

    printf("::testing Append\n");
    NPT_String l = "blabla";
    l.Append("blibliblo", 6);
    StringTest("append(const char*, int size)", l, "blablablibli");
    NPT_String a;
    a.Append("bloblo", 3);
    StringTest("append to NULL", a, "blo");

    printf("::testing Reserve\n");
    NPT_String r = "123";
    r.Reserve(100);
    IntTest("size of string not changed", 3, r.GetLength());
    r += "4";
    r += "5";
    r += "6";
    NPT_String r2 = r; // make a new reference
    r += "7";
    r += "8";
    r2 += "a";
    r2 += "b";
    StringTest("string r not changed", r, "12345678");
    StringTest("string r2 not changed", r2, "123456ab");

    printf(":: testing substring");
    NPT_String sup("abcdefghijklmnopqrstub");
    NPT_String sub = sup.SubString(0, 2);
    StringTest("substring [0,2] of 'abcdefghijklmnopqrstub'", sub, "ab");
    sub = sup.SubString(3, 4);
    StringTest("substring [3,4] of 'abcdefghijklmnopqrstub'", sub, "defg");
    sub = sup.SubString(100, 5);
    StringTest("substring [100,5] of 'abcdefghijklmnopqrstub'", sub, "");
    sub = sup.SubString(8,100);
    StringTest("substring [8,100] of 'abcdefghijklmnopqrstub'", sub, "ijklmnopqrstub");
    printf(":: decl NPT_String sub2(p2, 1, 2);\n");

    printf(":: testing trims");
    NPT_String trim = "*&##just this$&**";
    trim.TrimLeft('*');
    StringTest("TrimLeft('*') of '*&##just this$&**'", trim, "&##just this$&**");
    trim.TrimLeft("*&##");
    StringTest("TrimLeft('&*##')", trim, "just this$&**");
    trim.TrimRight('*');
    StringTest("TrimRight('*')", trim, "just this$&");
    trim.TrimRight("*&##");
    StringTest("TrimRight('*&##')", trim, "just this$");
    trim = "*&##just this$&**";
    trim.Trim("$&*#");
    StringTest("Trim('$&*#') of '*&##just this$&**'", trim, "just this");
    trim = "\r\njust this\t   \r\n";
    trim.Trim();
    StringTest("Trim() of '\\r\\njust this\\t   \\r\\n'", trim, "just this");

    printf(":: testing operator+=(NPT_String&)\n");
    NPT_String o1 = "hello";
    NPT_String o2 = ", gilles";
    o1 += o2;
    StringTest("operator +=", o1, "hello, gilles");
    o1 += ", some more";
    StringTest("operator +=", o1, "hello, gilles, some more");

    o1 = "abc";
    o1 += '#';
    StringTest("operator+=(char)", o1, "abc#");

    o1 = "hello";
    o2 = ", gilles";
    NPT_String o3 = o1+o2;
    StringTest("operator+(NPT_String&, NPT_String&)", o3, "hello, gilles");
    o3 = o1+", gilles";
    StringTest("operator+(NPT_String&, const char*)", o3, "hello, gilles");
    o3 = "I say:"+o1;
    StringTest("operator+(const char*, NPT_String&)", o3, "I say:hello");
    o3 = NPT_String("one, ") + "two";
    StringTest("NPT_String(\"one, \") + \"two\";", o3, "one, two");

    printf(":: testing operator[]\n");
    o1 = "abcdefgh";
    IntTest("o1[0]", 'a', o1[0]);
    IntTest("o1[1]", 'b', o1[1]);
    IntTest("o1[2]", 'c', o1[2]);
    o1[0] = '7';
    IntTest("o1[0]", '7', o1[0]);

    printf(":: testing operator comparisons\n");
    CompareTest(">",  "abc", "abc", NPT_String("abc") >  "abc", 0);
    CompareTest(">=", "abc", "abc", NPT_String("abc") >= "abc", 1);
    CompareTest("==", "abc", "abc", NPT_String("abc") == "abc", 1);
    CompareTest("!=", "abc", "abc", NPT_String("abc") != "abc", 0);
    CompareTest("<",  "abc", "abc", NPT_String("abc") <  "abc", 0);
    CompareTest("<=", "abc", "abc", NPT_String("abc") <= "abc", 1);

    CompareTest(">",  "abc", "ab", NPT_String("abc") >  "ab", 1);
    CompareTest(">=", "abc", "ab", NPT_String("abc") >= "ab", 1);
    CompareTest("==", "abc", "ab", NPT_String("abc") == "ab", 0);
    CompareTest("!=", "abc", "ab", NPT_String("abc") != "ab", 1);
    CompareTest("<",  "abc", "ab", NPT_String("abc") <  "ab", 0);
    CompareTest("<=", "abc", "ab", NPT_String("abc") <= "ab", 0);

    CompareTest(">",  "ab", "abc", NPT_String("ab") >  "abc", 0);
    CompareTest(">=", "ab", "abc", NPT_String("ab") >= "abc", 0);
    CompareTest("==", "ab", "abc", NPT_String("ab") == "abc", 0);
    CompareTest("!=", "ab", "abc", NPT_String("ab") != "abc", 1);
    CompareTest("<",  "ab", "abc", NPT_String("ab") <  "abc", 1);
    CompareTest("<=", "ab", "abc", NPT_String("ab") <= "abc", 1);

    CompareTest(">",  "bc", "abc", NPT_String("bc") >  "abc", 1);
    CompareTest(">=", "bc", "abc", NPT_String("bc") >= "abc", 1);
    CompareTest("==", "bc", "abc", NPT_String("bc") == "abc", 0);
    CompareTest("!=", "bc", "abc", NPT_String("bc") != "abc", 1);
    CompareTest("<",  "bc", "abc", NPT_String("bc") <  "abc", 0);
    CompareTest("<=", "bc", "abc", NPT_String("bc") <= "abc", 0);

    CompareTest(">",  "abc", "bc", NPT_String("abc") >  "bc", 0);
    CompareTest(">=", "abc", "bc", NPT_String("abc") >= "bc", 0);
    CompareTest("==", "abc", "bc", NPT_String("abc") == "bc", 0);
    CompareTest("!=", "abc", "bc", NPT_String("abc") != "bc", 1);
    CompareTest("<",  "abc", "bc", NPT_String("abc") <  "bc", 1);
    CompareTest("<=", "abc", "bc", NPT_String("abc") <= "bc", 1);

    printf(":: testing Compare\n");
    CompareTest("cnc", "abc", "abc", NPT_String("abc").Compare("abc", true), 0);
    CompareTest("cnc", "AbC3", "aBC3", NPT_String("AbC3").Compare("aBC3", true), 0);
    CompareTest("cnc", "AbCc", "aBcD", NPT_String("AbCc").Compare("aBcD", true), -1);
    CompareTest("cnc", "AbCC", "aBcd", NPT_String("AbCC").Compare("aBcd", true), -1);
    CompareTest("cnc", "bbCc", "aBcc", NPT_String("bbCc").Compare("aBcc", true), 1);
    CompareTest("cnc", "BbCC", "aBcc", NPT_String("BbCC").Compare("aBcc", true), 1);

    printf(":: testing MakeLowercase\n");
    NPT_String lower = "abcdEFGhijkl";
    lower.MakeLowercase();
    EqualTest("MakeLowercase (noref)", "abcdEFGhijkl", lower, "abcdefghijkl");
    lower = "abcdEFGhijkl";
    NPT_String lower2 = lower;
    lower2.MakeLowercase();
    EqualTest("MakeLowercase (ref)", "abcdEFGhijkl", lower2, "abcdefghijkl");

    printf(":: testing MakeUppercase\n");
    NPT_String upper = "abcdEFGhijkl";
    upper.MakeUppercase();
    EqualTest("MakeUppercase (noref)", "abcdEFGhijkl", upper, "ABCDEFGHIJKL");
    upper = "abcdEFGhijkl";
    NPT_String upper2 = upper;
    upper2.MakeUppercase();
    EqualTest("MakeUppercase (ref)", "abcdEFGhijkl", upper2, "ABCDEFGHIJKL");

    printf(":: testing ToLowercase\n");
    lower = "abcdEFGhijkl";
    EqualTest("ToLowercase", "abcdEFGhijkl", lower.ToLowercase(), "abcdefghijkl");

    printf(":: testing ToUppercase\n");
    upper = "abcdEFGhijkl";
    EqualTest("ToUppercase", "abcdEFGhijkl", lower.ToUppercase(), "ABCDEFGHIJKL");

    printf(":: testing Find (s=\"au clair de la lune\")\n");
    s = "au clair de la lune";
    int f = s.Find("au");
    IntTest("Find(\"au\")", f, 0);
    f = s.Find("clair");
    IntTest("Find(\"clair\")", f, 3);
    f = s.Find("luneb");
    IntTest("Find(\"luneb\")", f, -1);
    f = s.Find((const char*)NULL);
    IntTest("Find(NULL)", f, -1);
    f = s.Find("hello");
    IntTest("Find(\"hello\")", f, -1);
    f = s.Find("");
    IntTest("Find(\"\")", f, 0);
    f = s.Find("clair", 2);
    IntTest("Find(\"clair\", 2)", f, 3);
    f = s.Find("clair", 100);
    IntTest("Find(\"clair\", 100)", f, -1);
    f = s.Find("au clair de la lune");
    IntTest("Find(\"au clair de la lune\")", f, 0);
    f = s.Find("au clair de la lune mon ami");
    IntTest("Find(\"au clair de la lune mon ami\")", f, -1);
    f = s.Find('c');
    IntTest("Find('c')", f, 3);
    NPT_String s1;
    f = s1.Find("hello");
    IntTest("Find() in empty string", f, -1);

    printf(":: testing ReverseFind\n");
    s = "aabbccaa";
    f = s.ReverseFind("a");
    IntTest("", f, 7);
    f = s.ReverseFind("a", 1);
    IntTest("", f, 6);
    f = s.ReverseFind("a", 9);
    IntTest("", f, -1);
    f = s.ReverseFind("aab");
    IntTest("", f, 0);
    f = s.ReverseFind((const char*)NULL);
    IntTest("", f, -1);
    f = s.ReverseFind("");
    IntTest("", f, -1);
    f = s.ReverseFind("aa", 1);
    IntTest("", f, 0);
    f = s.ReverseFind("aabbccaa");
    IntTest("", f, 0);
    f = s.ReverseFind("aabbccaaa");
    IntTest("", f, -1);

    printf(":: testing StartsWith\n");
    bool b = s.StartsWith("");
    IntTest("", b, 0);
    b = s.StartsWith("aaba");
    IntTest("", b, 0);
    b = s.StartsWith("aabbccaaa");
    IntTest("", b, 0);
    b = s.StartsWith("aabb");
    IntTest("", b, 1);

    printf(":: testing EndsWith\n");
    b = s.EndsWith("");
    IntTest("", b, 0);
    b = s.EndsWith("aaba");
    IntTest("", b, 0);
    b = s.EndsWith("aabbccaaa");
    IntTest("", b, 0);
    b = s.EndsWith("ccaa");
    IntTest("", b, 1);

    printf(":: testing Replace\n");
    NPT_String r0 = "abcdefghijefe";
    r0.Replace('e','@');
    StringTest("Replace(char, char)", r0, "abcd@fghij@f@");
    NPT_String r1 = r0;
    r1.Replace('@', '#');
    StringTest("Replace(char, char)", r1, "abcd#fghij#f#");

    printf(":: testing Insert\n");
    NPT_String in0;
    in0.Insert("hello", 1);
    StringTest("Insert into NULL, past end", in0, "");
    in0.Insert("hello");
    StringTest("Insert into NULL, at start", in0, "hello");
    in0.Insert("yoyo");
    StringTest("Insert at start", in0, "yoyohello");
    in0.Insert("yaya", 3);
    StringTest("Insert at 3", in0, "yoyyayaohello");

    return 0;
}
