#ifndef __COMPILER_H__
#define __COMPILER_H__

#include "lexer.h"
#include "ir.h"

extern void parse();

#endif

/*

.h檔案(header)的中的#ifndef功能:

Q :

當  1.有兩個C文件要include同一個header
    2.編譯時這兩個C文件要一同編譯成一個可運行文件
會產生大量的聲明衝突！

A :
不管你的header會不會被多個文件引用，
header的內容都放在#ifndef和#endif中，
可解決此問題！

格式 :
#ifndef <標識> --- (標識可以自行命名)
#define <標識>

......
......

#endif

*/

/*

extern用法 : 一般會在標頭檔案(.h)中使用extern給出全域性變數的宣告！

宣告和定義的區別 : 定義只有一次，宣告沒有限制。

*定義:就是賦予此變數或函數一個值。
*宣告:因為有多個檔案，所以"宣告"是告訴整個檔案系統、告訴有include此.h檔的那些檔案：
「本.h檔宣告了此變數或函數，所以include本.h檔的這些檔案整合起來執行時，若是發生名字相同的情況，是不會發生衝突的！」

E.g.
compiler.h中的extern void parse(); (宣告)
或lexer中的extern char *typeName[]; (宣告)

並在原始檔(.c)中賦予void parse()、char *typeName[]...etc值（定義)(only once）

*/