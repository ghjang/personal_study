# git 관련 메모

* `git init`
  * `git init` 명령어는 '비어있는 작업 폴더' 뿐만 아니라 '비어있지 않은 로컬 작업 폴더'에서도 실행할 수 있다.
  * `git init` 명령어를 실행하면 '.git' 폴더가 생성된다.
  * '.git' 폴더는 'git 저장소'로 지정된 작업 폴더를 관리하는데 사용되는 곳으로 git 설정 파일등이 저장된다. .git 폴더는 작업 폴더의 최상위에 1개만 생성된다.
  * 현재의 로컬 git 저장소 작업 폴더를 git이 관리하는 폴더가 아닌 일반 폴더로 만들고 싶다면 '.git' 폴더를 단순히 삭제하면 된다.

* `git config`
  * 로컬에서 작업중인 git 저장소에 'user.name' 또는 'user.email' 계정 관련 정보를 직접 설정하지 않으면, 현재 로그인한 사용자의 '홈 폴더' 위치에 존재하는 '.gitconfig' 파일에 'global'하게 설정된 계정 정보를 참조시도하게 된다.
  * 'global'하게 계정 정보를 설정하는 방법은 `git config --global user.name "사용자 이름"` 또는 `git config --global user.email "사용자 이메일"` 명령어를 사용하면 된다.
  * 'global'하게 설정된 계정 정보를 삭제하고 싶다면, `git config --global --unset user.name` 또는 `git config --global --unset user.email` 명령어를 사용하면 된다.
  * 'local' 작업 폴더 저장소에 계정 정보를 설정하고 싶다면, `git config user.name "사용자 이름"` 또는 `git config user.email "사용자 이메일"` 명령어를 사용하면 된다.
  * 'local' 작업 폴더 저장소에서 계정 정보를 삭제하고 싶다면, `git config --unset user.name` 또는 `git config --unset user.email` 명령어를 사용하면 된다.
  * FIXME: 'local' 작업 폴더 저장소와 'global' 계정 정보를 모두 설정하고 싶다면, `git config --local user.name "사용자 이름"` 또는 `git config --local user.email "사용자 이메일"` 명령어를 사용하면 된다.
  * 'local' 작업 폴더 저장소와 'global' 계정 정보를 모두 삭제하고 싶다면, `git config --unset-all user.name` 또는 `git config --unset-all user.email` 명령어를 사용하면 된다.
  * 'local' 작업 폴더 저장소와 'global' 계정 정보가 모두 설정되어 있는 경우, 'local' 작업 폴더 저장소의 계정 정보가 우선적으로 사용된다.
  * FIXME: '홈 폴더' 위치의 '.gitconfig' 파일에도 계정 관련 정보가 없으면 어떻게 되는지 확인 필요함. '로그인 계정명'을 'user.name'으로 암묵적으로 사용? 'user.email' 정보는?
