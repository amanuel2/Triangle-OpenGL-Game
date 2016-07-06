-a

 jmp 115
 db 'Hello, World!$'
 
-a 115
 mov ah, 09
 mov dx, 102
 int 21 
 int 20

-crx
-n HelloWorld.com
-w
