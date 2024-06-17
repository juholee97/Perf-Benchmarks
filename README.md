# Perf-Benchmarks

# 기능이 유사한 동작에 대한 퍼포먼스를 벤치를 통해 확인 & 정리하고자 생성된 Repo.

## TEST 01. 함수 호출 횟수에 따른 lamda 와 std::function 성능 비교. ( https://github.com/juholee97/Perf-Benchmarks/tree/main/Perf-Bench_lamda_func )


std::function 이 TypeErasure 패턴 기반이기에 느리다는 점은 알고 있었으나 
실제로 lamda 호출에 비해 얼마나 차이나는지 체크하고 비교하고자 함.

### 테스트 수행

1 ~ 10만 번 각각의 함수를 반복 호출 했을 때, lamda 와 std::func 의 성능 비교.


![image](https://github.com/juholee97/Perf-Benchmarks/assets/156589691/0024e614-21e6-4c57-93f2-f8ab46111b07)

f_lamda를 통한 함수 1회 호출 시 평균 소요 시간 : 약 0.000001951564ms

f_stdFunc를 통한 함수 1회 호출 시 평균 소요 시간 : 약 0.000028202051ms

호출 횟수가 커질수록 std::function의 성능이 lamda의 성능에 비해 매우 좋지 않음을 확인할 수 있었음. (테스트 상 약 14배)






## TEST 02. Class 초기화 관점에서 std::swap을 사용했을 때, assign 과 성능 비교. ( https://github.com/juholee97/Perf-Benchmarks/tree/main/Perf-Bench_assign_swap )


std::swap 은 assign과 비교했을 때, 어느 정도 성능 상의 차이가 발생하는지 1~10만 번의 반복 호출을 통해 평균 소요 시간을 측정.


### 테스트 수행

1 ~ 10만 번 각각의 함수를 반복 호출 했을 때, assign 와 std::swap 의 성능 비교.


![image](https://github.com/juholee97/Perf-Benchmarks/assets/156589691/6c914619-4c4b-4c89-89cb-acf3a0ff203b)

assign을 통한 초기화 1회 호출 시 평균 소요시간 :	약 0.000035536ms	

std::swap을 통한 초기화 1회 호출 시 평균 소요시간 : 약 0.000094656ms

class에 대해 초기화를 진행했을 때 std::swap이 assign과 비교했을 때 약 2.7 배의 속도 차이를 보임.

이는 std::swap이 두 객체의 값을 교환하기 위해 세 번의 이동 혹은 복사연산을 수행하기 때문에, 일정 수준 이상의 연산 비용을 초래함.

assign의 경우, 일반적으로 동작이 간단하며, 작은 클래스일수록 비용이 낮음.

추가적으로 컴파일러 최적화를 빼먹을 수 없는데, 컴파일러 최적화는 동작 속도 개선에 큰 영향을 주며, 특히 단순한 할당 연산인 assign의 경우 컴파일러가 매우 효율적으로 최적화 할 수 있음.

반면, std::swap의 경우 중간 변수 및 여러 단계의 할당을 포함하고 있으므로 컴파일러 측면에서 봤을 때, 최적화가 더 어려울 수 있음.

결론적으로, class를 초기화 할 때, std::swap을 사용하여 초기화 시키는것 보다는 assign 연산을 통해 초기화 시키는 것이 성능적인 측면에서 유리함.

다만 추가적으로 생각해볼 내용으로, class의 size가 매우 큰 경우 일일히 assign으로 초기화 하는것이 빠를지, class 생성 후 std::swap을 통해 초기화 시키는 것이 좋을지는 고려해볼만 하다고 생각함.
