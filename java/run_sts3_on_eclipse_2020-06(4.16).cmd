REM 로컬에 포터블하게 설치된 OpenJDK 1.8 버전을 이용해 Eclipse 2020-06(4.16) IDE에 Spring Tools 3 플러그인이 설치된 Spring Tool Suite 3을 실행한다.

set JAVA_HOME=C:\_u2l\_dev_env\jdk\OpenJDK8U-jdk_x64_windows_hotspot_8u372b07\jdk8u372-b07
set PATH=%SystemRoot%;%SystemRoot%\system32;%JAVA_HOME%\bin

java -version
where java

start C:\_u2l\_dev_env\eclipse\spring-tool-suite-3.9.15.RELEASE-e4.16.0-win32-x86_64\sts-bundle\sts-3.9.15.RELEASE\STS.exe
