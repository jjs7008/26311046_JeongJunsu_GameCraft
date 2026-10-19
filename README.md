# 달빛 배송작전 (Moonlight Delivery)

C++ / glc2d로 만드는 2D 수집·회피 게임. **현재 1주차 시제품**입니다.

## 프로젝트 상태

- 구현 완료: glc2d 게임 창, WASD/방향키 이동, 플레이어 위치 제한, 택배와 위험 물체 낙하 표현
- 추후 구현: 충돌, 수집, 체력, 점수, 타이머, 화면 전환, 3개 스테이지, 애니메이션
- 게임 기획서: [1주차 기획서](Docs/Week1_GamePlan.md)

## 개발 환경

Windows / Visual Studio 2022 / C++ / glc2d NuGet 패키지 / Microsoft.DXSDK.D3DX NuGet 패키지

## 실행 방법

1. `MoonlightDelivery/MoonlightDelivery.sln`을 Visual Studio 2022로 연다.
2. 솔루션 우클릭 → **NuGet 패키지 복원**을 선택한다 (프로젝트의 `packages.config` 참조).
3. 플랫폼을 `x64`, 구성을 `Debug`로 두고 로컬 Windows 디버거로 실행한다.
4. WASD 또는 방향키로 로봇을 이동한다. 택배와 장애물은 아직 시각적 테스트 용도다.

**주의:** 이 환경에서 Windows용 빌드/실행 테스트는 수행하지 못했다. NuGet 패키지 복원 또는 라이브러리 경로 오류가 나면 Visual Studio 출력 창을 확인해야 한다. 샘플 프로젝트 설정은 제공 SDK의 `app_nuget/Ex04_Keyboard`를 바탕으로 했다.

## 제출 및 Git 관리

교수님 지침에 맞는 저장소 이름: `학번_이름(영문)_GameCraft`.

초기 커밋 후 1주차 태그 `f1`을 만들고 GitHub로 푸시한다. `.vs`, 빌드 산출물, 다운로드된 `packages` 폴더는 올리지 않는다.

## 라이브러리 / 참고 자료

- [glc2d 라이브러리 소스 및 샘플](https://github.com/3dapi/glc2d_lib)
- [glc2d NuGet](https://www.nuget.org/packages/glc2d)
- [Microsoft.DXSDK.D3DX](https://www.nuget.org/packages/Microsoft.DXSDK.D3DX/9.29.952.8)

이미지 3종은 이 과제용으로 직접 생성한 간단한 PNG 도형 리소스다.
