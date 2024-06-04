# Perf-Benchmarks

# 기능이 유사한 동작에 대한 퍼포먼스를 벤치를 통해 확인 & 정리하고자 생성된 Repo.

## TEST 01. 함수 호출 횟수에 따른 lamda 와 std::function 성능 비교.
std::function 이 TypeErasure 패턴 기반이기에 느리다는 점은 알고 있었으나 
실제로 lamda 호출에 비해 얼마나 차이나는지 체크하고 비교하고자 함.

### 테스트 수행

1 ~ 10만 번 함수를 반복 호출 했을 때, lamda 와 std::func 의 성능 비교.


![image](https://github.com/juholee97/Perf-Benchmarks/assets/156589691/0024e614-21e6-4c57-93f2-f8ab46111b07)

f_lamda를 통한 함수 1회 호출 시 평균 소요 시간 : 0.000001951564ms
f_stdFunc를 통한 함수 1회 호출 시 평균 소요 시간 : 0.000028202051ms
호출 횟수가 커질수록 std::function의 성능이 lamda의 성능에 비해 매우 좋지 않음을 확인할 수 있었음. (테스트 상 약 14배)
