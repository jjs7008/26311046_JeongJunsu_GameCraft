# 달빛 배송작전 (Moonlight Delivery)

C++ / glc2d 2D 수집·회피 아케이드 게임. **현재 3주차: 핵심 게임 로직 구현 버전**입니다.

## 실행
`MoonlightDelivery/MoonlightDelivery.sln`을 Visual Studio 2022에서 열고 NuGet 복원 후 실행하세요. 패키지: `glc2d 0.1.0.8`, `Microsoft.DXSDK.D3DX 9.29.952.8`.

## 조작·규칙
- Enter: 시작/재시작, WASD 또는 방향키: 이동, Esc: 타이틀로
- 택배 획득 +10점, 위험물에 닿으면 HP -1
- HP 0: 게임오버, 100점: 클리어
- 피격 직후 잠시 무적, 점수·HP·경과시간 표시

## 개발 문서
- [1주차 기획서](Docs/Week1_GamePlan.md)
- [2주차 개발 문서](Docs/Week2_Development.md)
- [3주차 개발 문서](Docs/Week3_Development.md)

## 주차별 기록
`f1`: 기획 / `f2`: 리소스·기본 클래스 / `f3`: 충돌·점수·체력·플레이 / `f4`: 스테이지 확장 예정
