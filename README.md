# 달빛 배송작전 (Moonlight Delivery)

C++ / glc2d를 사용하는 2D 수집·회피 아케이드 게임. **4주차: 스테이지 확장 및 동적 연출 구현** 버전입니다.

## 조작
- Enter: 게임 시작 / 재시작
- WASD 또는 방향키: 이동
- Esc: 타이틀로 돌아가기

## 게임 규칙
떨어지는 택배를 획득하면 10점, 위험 물체와 충돌하면 체력이 1 감소합니다. 체력은 3이며 피격 직후 잠시 무적 시간이 주어집니다. 총 3스테이지를 진행하고 180점에 도달하면 게임 클리어입니다.

## 스테이지
| 스테이지 | 누적 점수 목표 | 차별점 |
|---|---:|---|
| 1 | 50 | 기본 장애물 1개 |
| 2 | 110 | 장애물 2개, 빠른 낙하 |
| 3 | 180 | 더 빠른 낙하, 좌우 이동 장애물 |

## 개발 환경
Visual Studio 2022 / Windows / C++ / NuGet `glc2d` + `Microsoft.DXSDK.D3DX`. 솔루션: `MoonlightDelivery/MoonlightDelivery.sln`.

## 개발 문서
- [1주차 게임 기획서](Docs/Week1_GamePlan.md)
- [2주차 개발 정리](Docs/Week2_Development.md)
- [3주차 개발 정리](Docs/Week3_Development.md)
- [4주차 개발 정리](Docs/Week4_Development.md)

## 검증 안내
첨부 소스를 바탕으로 4주차 구현을 작성했습니다. Windows에서 실제 컴파일·실행은 이 환경에서 검증하지 못했으므로 로컬 실행 후 `f4` 릴리스를 게시해주세요.
