**코딩 컨벤션**

-클래스, 함수, 변수명 생략 자제 -> 명확하게 하기

-형변환 명시하기

-변수는 camelCase

-함수는 PascalCase

-프라이빗 변수는 _로 시작 + camelCase

-클래스 기본 변수 초기화는 선언과 동시에

-포인터는 p로 명시하기 ex)pPointer

-글로벌변수는 g_로 명시하기 ex)g_global

-라인이 길어지면 짤라서!-> 파일 많이 띄어놓고 해서 양해 부탁.

-로컬 변수는 본인 편한대로!

이외에 자유. 여러분들을 믿습니다~읽을때 불편하지만 않으면됨

ex)
class MyClass 
{
  //클래스 기본 변수 초기화는 선언과 동시에
  int _myPrivateVariable=0;  // 
  

public:
  int myPublicVariable;  // 퍼블릭 변수는 camelCase
  // 포인터는 포인터라고 이름에 명시하시오. e.i. pObj or objPointer
  OtherObject* pOtherObj, otherObjPointer;

  // 이니셜라이징 리스트가 많으면 짤라서!
  MyClass
(
    int myPrivateVar, 
    int myPublicVar, 
    OtherObject* pObj, 
    OtherObject& rObj
) 
  : _myPrivateVariable(myPrivateVar), 
    myPublicVariable(myPublicVar), 
    pOtherObj(pObj), rOtherObj(rObj) {}

  void MyPublicFunction() 
{  //함수는 PascalCase
    int a;  // 로컬 변수는 본인 편한대로!
    return;
}

  bool MyFunctionWithLongParameterList
(  // 함수 파라미터가 많은면 짤라서!
    int a,            // a
    double d,         // d
    Object* pObj,     // pObj
) 
{
    int localA=a;    // 로컬 변수는 본인 편한대로!
    double local_d=d // 로컬 변수는 본인 편한대로!
    
    // 라인이 길어지면 짤라서!
    return (a == 1) && 
      (d == 0.7) && 
      (pObj != nullptr) &&
      (pReserved == nullptr);
  }
};


**Git**
-커밋하고 푸시하기전에 무조건 팀원들한테 말하고 커밋하고 푸시하기.
	
-커밋 메시지 무조건 남기기. 간단한 이유에도 "temp" 라도 메시지 남기기

이외에 딱히 특별한거 x 여러분들을 믿습니다~


