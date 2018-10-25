#길앞잡이(스마트 맹인 지팡이)

#프로젝트 설명
지하철을 많이 이용하다보면 가끔씩 시각장애인을 보게 됩니다. 언제나 흰 지팡이와 함께한 채로
다닙니다. 또한 시각장애인이 있지 않아도 볼 수 있는 것이 있습니다. 점자블록입니다. 누구나
그 존재를 알지만 누구도 관심을 가지지 않습니다. 하지만 시각장애인에게는 둘 다 없으면 안되는
소중한 보행 보조수단 입니다. 이 두가지를 접목하여 시각장애인이 보행을 조금 더 안전하게 할 수
있도록 흰 지팡이와 점자블록을 접목하여 시각장애인이 점자블록을 따라 걷다가 자신이 가는 방향의
점자블록에 지팡이를 대면 RFID를 통해 사용자에게 가고자 하는 방향에 있는 장소를 알려주는
지팡이를 만들었습니다. 또한 보조수단으로 초음파를 이용한 장애물감지, GPS를 활용한 위치알림,
LED를 활용한 안전등, SOS기능을 추가하였습니다.

#프로젝트 구현 내용

사용 부품
- 아두이노 UNO
- 초음파센서
- 엑티브부저
- LED
- 16X2 character LCD
- 조이스틱
- Tact스위치

I) 지팡이 자체 기능
 - 4가지 기능을 맹인이 한 손으로 컨트롤 할 수 있도록 조이스틱을 활용
 - 조이스틱을 한 번 클릭한 후 원하는 모드 방향으로 1초동안 움직이면 모드 실행
 - 모든 모드는 타이머 인터럽트를 통해 여러 모드를 실행해도 효율적으로 각자의 일을 할 수 있게 만
 
1. 초음파를 이용하여 허리 위쪽의 장애물을 인식하여 사용자에게 거리를 진동으로 알려주는 기능
 - 주변의 물체나 사람이 많은 지하철 안 같은 곳에서는 끌 수 있게 on/off 가능하게 제작
 - 실제 작품에서는 진동모터의 부재로 부저로 대체

2. GPS를 통해 보호자에게 맹인의 위치를 실시간으로 전송하는 기능
 - 사용자가 스스로의 위치를 알리고 싶지 않을 경우를 대비하여 on/off 가능하게 제작
 - 타이머 인터럽트를 활용하여 다른 기능과 함께 하더라도 항상 10초마다 GPS값을 보내도록 설정
 - 실제 작품에서는 블루투스와 GPS의 부재로 시리얼 통신망으로 임의의 GPS값을 보내어 확인
 - 실제로 통신이 안 되기 때문에 임의의 값을 받았다는 가정하에 어플에서 맹인 위치 뜨게 어플 제작

3. SOS기능
 - 사용자가 본인이 위협을 느꼈을 때 실행을 하여 경보가 울리고, LED가 깜빡이며, 혹여 사고로 기절했을 때
   누군가가 와서 보게 된다면 보호자와 연락할 수 있도록 보호자의 연락처와 사용자의 이름이 LCD로 표시됨.
 - 또한 보호자에게 GPS와 SOS신호를 보내어 보호자가 나의 위치와 현재 위험한 상황이라는 것을 알 수 있게 함.
 - 실제 작품에서는 블루투스와 GPS의 부재로 시리얼 통신망으로 임의의 GPS값을 보내어 확인
 - 실제로 통신이 안 되기 때문에 임의의 값을 받았다는 가정하에 어플에서 맹인의 위치와 경보, PUSH알림,
   112로 전화연결을 하도록 어플 제작
   
4. 야간 안전LED
 - 사용자가 야간에 다닐 때 다른 사람이 사용자를 감지할 수 있도록 함.
 - 맹인은 아예 앞이 안보이는 것이 아닌 빛을 감지할 수 있기 때문에 스스로 어두운 것을 감지하고 켜고 끌 수 있게 함.
 
 II)지팡이와 점자블록 연동한 기능
  - 지팡이를 사용자가 가고자 하는 위치의 점자블록에 대면 점자블록에 심어져 있는 RFID태그가 지팡이에 장소를
    알려주고 이를 감지한 지팡이는 그것을 사용자에게 음성으로 알려준다.
  - 실제 작품에서는 RFID통신사용이 불가하여 바닥에 대는 모습을 보여주기 위해 스위치를 사용함.
  - 사람의 음성을 출력할 수 없기 때문에 위치 정보를 LCD로 보이게 함.
  
  #팀 소개
   - 11사단 병장 박일도
   - 3기갑여단 병장 이승호
