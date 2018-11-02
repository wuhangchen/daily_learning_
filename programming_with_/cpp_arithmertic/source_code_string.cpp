/*
 *记录字符串的相关算法实现。参考相应的源代码头文件可以借鉴。  
 *
 *
 */

namespace  source_code_{

    
    // 字符串拷贝算法。
    
        //版本1，拷贝指定数目的原端到目的端，要求目的端的长度必须大于原端，否则发生未定义的操作。
           char *
           strncpy(char *dest, const char *src, size_t n)
           {
               size_t i;

               for (i = 0; i < n && src[i] != '\0'; i++)
                   dest[i] = src[i];
               //目的是将dest端后部分的序列设定为'\0'.
               for ( ; i < n; i++)
                   dest[i] = '\0';

               return dest;
           }


        //版本2，
                    












}
