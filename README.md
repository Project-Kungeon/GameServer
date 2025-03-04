# ℹ️ 소개

졸업프로젝트 전용 게임 서버입니다.

---

## 🚥 기능

- 플레이어들의 공격(스킬), 이동, 아이템 상호작용 등 서버 - 클라이언트 간 이벤트 동기화
- Tick 생성으로 인한 쿨타임 및 버프 시간 계산
- 몬스터(Rampage) 패트롤 기능
- 지연 발생에 따른 일관성/반응성 개선(미완, 업데이트 예정)

---

## ⚒️ 구조

![image](https://github.com/user-attachments/assets/35b915b0-1480-4447-99e8-7552cf057086)

- Session : 클라이언트의 접속이 성공했을 경우 생성되는 통신 대리자 클래스
- PacketHandlers : 전투, 일반, 라운드 등 패킷 핸들러(직렬화/역직렬화 담당, 정적 클래스)
- Utils : Player, Monster, Math, Packet 등 공통적으로 사용되는 Utils (정적 클래스)
- GameRoom : 실제 인게임 월드에 접속 혹은 소환된 오브젝트 관리 / 송신된 패킷 이벤트를 처리하여 반영하는 공유 자원 / 접속한 플레이어에게 패킷을 전달 혹은 브로드캐스트 담당
- JobQueue : Io_context로부터 할당된 strand 객체로 구현(각 메모리마다 고유 strand 소유 중)

---

## 📁 실행 방법

BWSever.exe 와 libprotobufd.dll이 같은 위치에 있어야 합니다. 로컬호스트의 424 포트로 배포되며, exe를 실행하면 됩니다.
(단, 현재 매칭 시스템이 없기 때문에 실행 시 몬스터 스폰 및 라운드 시작이 되어버립니다)

+ __현재 레포지토리 상태에서 빌드를 할 수 없습니다__
+ [BoostAsio 1.83.0](https://www.boost.org/users/download/)의 hpp 폴더를 참조 디렉토리에 추가해주셔야 빌드가 가능합니다.

## 📌 개발 일지

[노션 링크](https://citrine-index-9b7.notion.site/b46d5981e24845b897ccf5a601b12b03?pvs=73)
