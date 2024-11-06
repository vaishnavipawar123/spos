import java.io.*;
import java.util.*;
class B1 {
static {
System.loadLibrary("B1");
}
private native int add(int a, int b);
private native int sub(int a, int b);
private native int mult(int a, int b);
private native int div(int a, int b);
public static void main(String[] args) {
Scanner sc=new Scanner(System.in);
int a, b,ch;
System.out.println("\nEnter value of a : ");
a = sc.nextInt();
System.out.println("\nEnter value of b : ");
b = sc.nextInt();
do
{
System.out.println("\nENTER YOUR CHOICE : ");
ch = sc.nextInt();
switch(ch)
{
case 1 : new B1().add(a,b);
break;
case 2 : new B1().sub(a,b);
break;
case 3 : new B1().mult(a,b);
break;
case 4 : new B1().div(a,b);
break;
default : System.out.println("Your choice is wrong.");
}
}while(ch<5);
}
}


) admin1@413-24:~$ javac B1.java
(base) admin1@413-24:~$ javah -jni B1
(base) admin1@413-24:~$ locate jni.h
/home/admin1/.vscode/extensions/redhat.java-1.32.0-linux-x64/jre/17.0.11-linux-x86_64/include/jni.h
/home/admin1/.vscode/extensions/redhat.java-1.33.0-linux-x64/jre/17.0.11-linux-x86_64/include/jni.h
/opt/android-studio/jre/include/jni.h
/snap/intellij-idea-community/495/jbr/include/jni.h
/snap/intellij-idea-community/515/jbr/include/jni.h
/snap/vlc/3721/usr/lib/jvm/java-8-openjdk-amd64/include/jni.h
/snap/vlc/3777/usr/lib/jvm/java-8-openjdk-amd64/include/jni.h
/usr/lib/jvm/java-11-openjdk-amd64/include/jni.h
/usr/lib/jvm/java-8-openjdk-amd64/include/jni.h
/usr/lib/jvm/java-8-oracle/include/jni.h
/usr/local/java/jdk1.8.0_181/include/jni.h
(base) admin1@413-24:~$ gcc -I/usr/lib/jvm/java-8-openjdk-amd64/include -I/usr/lib/jvm/java-8-openjdk-amd64/include/linux -o libB1.so -shared -fPIC B1.c
(base) admin1@413-24:~$ java -Djava.library.path=. B1

Enter value of a : 
50

Enter value of b : 
20

ENTER YOUR CHOICE : 
1

50 + 20 = 70

