# M2 MacBook Air에서 오라클DB서버 도커 컨테이너 구동법

## 오라클 서버 시작

1. 'brew' 패키지 매니저 설치
    - <https://brew.sh> 에서 설치법 확인후 설치
1. 'colima' 컨테이너 런타임 설치
    - <https://github.com/abiosoft/colima> 에서 `brew`를 이용한 설치법 확인후 설치
1. 'colima' 구동

    '터미널'에서 다음 명령어를 실행할 것:

    ```zsh
    colima start --arch x86_64 --memory 1g
    ```

    메모리 사용량은 사용할 오라클 서버의 메모리 요구사항에 맞게 설정할 것.  
    참고로 11gR2의 경우 512MB를 권장하고 있음.

1. 'docker' 컨테이너 구동

    colima 런타임을 구동해놓은 상태에서 또다른 터미널을 (탭으로) 열고 다음 명령어를 실행할 것:

    ```zsh
    docker run -d --name oracle-11g -p 1521:1521 -e ORACLE_PASSWORD=<your_password> -v oracle-volume:/u01/app/oracle/oradata gvenzl/oracle-xe:11
    ```

    위 커맨드는 'Oracle XE 11gR2' 도커 컨테이너를 '도커허브'로부터 도커 이미지를 다운로드 받아서 구동시키는 것임.  
    좀더 자세한 사항은 <https://hub.docker.com/r/gvenzl/oracle-xe> 를 참고할 것.

---

## 오라클 서버 정지

서버 시작시 실행시킨 커맨드를 역순으로 실행해준다.

1. 'docker' 컨테이너 정지

    ```zsh
    docker stop <컨테이너 ID 또는 이름>
    ```

    참고로 `docker ps` 명령어로 컨테이너 ID 또는 이름을 확인할 수 있음.

1. 'colima' 정지

    ```zsh
    colima stop
    ```

---

## 기타 참고사항

- 'Docker Desktop'을 실행해 기본 도커 런타임을 통해서 'docker' 커맨드 툴을 사용하고자 했으나 다음과 같은 'colima' 런타임 관련 오류가 발생할 수 있음:

    ```zsh
    > docker image ls
    Cannot connect to the Docker daemon at unix:///Users/ghjang/.colima/default/docker.sock. Is the docker daemon running?
    ```

    이런 경우에는 다음 커맨드를 실행해서 'default' 런타임을 'Docker Desktop'으로 변경해주고 다시 실행하면 됨:

    ```zsh
    docker context use default
    ```

    참고로 'colima' 런타임 실행시 'docker' 커맨드의 컨텐스트가 자동으로 'colima' 쪽으로 변경되어 실행될 것임.
