# Perf-Benchmarks

# 기능이 유사한 동작에 대한 퍼포먼스를 벤치를 통해 확인 & 정리하고자 생성된 Repo.

## TEST 01. 함수 호출 횟수에 따른 lamda 와 std::function 성능 비교.
std::function 이 TypeErasure 패턴 기반이기에 느리다는 점은 알고 있었으나 
실제로 lamda 호출에 비해 얼마나 차이나는지 체크하고 비교하고자 함.

### 테스트 수행

1 ~ 10만번 호출 했을 때의 lamda 와 std::func 의 성능 비교.
 
