REM 로컬에 포터블하게 설치된 OpenJDK 1.8 버전을 이용해 Eclipse 2020-06(4.16) IDE를 실행한다.

set JAVA_HOME=C:\_u2l\_dev_env\jdk\OpenJDK8U-jdk_x64_windows_hotspot_8u372b07\jdk8u372-b07
set PATH=%SystemRoot%;%SystemRoot%\system32;%JAVA_HOME%\bin

java -version
where java

start C:\_u2l\_dev_env\eclipse\eclipse-jee-2020-06-R-win32-x86_64\eclipse\eclipse.exe
