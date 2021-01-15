# DSP Acid Rain Game
> '자료구조 실습' 수업에서 진행한 팀프로젝트입니다.

<img src="https://user-images.githubusercontent.com/48644958/102573912-e28d1880-4132-11eb-9713-d8bc35d8b664.png" width="90%"></img>

소켓을 활용해 최대 15명까지 접속 가능한 산성비 게임을 제작하였습니다.

서버에서 끄투 오픈소스 DB에서 다양한 주제의 단어를 받아온 후, 여러 사용자에게 전송해주는 형식으로 진행됩니다.
Text 기반으로 진행되는 게임을 감안하여, Loss에 안정적인 TCP를 통해 서버와 사용자가 소켓을 주고받도록 하였습니다.
또한, 사용자가 정해진 순서 없이 단어를 입력한다는 점에서, LinkedList 자료구조를 활용하여 삭제가 수월하도록 하였습니다.
마지막으로 사용자들끼리 공격 단어를 입력하는 경우, 자신을 제외한 나머지 사용자에게 해당 단어를 보낼 수 있도록하는 기능을 추가하였습니다.



## 게임 진행 영상

<iframe width="1280" height="720" src="https://youtu.be/vR3zpz9m9CI" frameborder="0" gesture="media" allowfullscreen=""></iframe>

## 개발 환경

> 운영체제 : Ubuntu 16.4
> 개발언어 : C++ / Python
> 사용 오픈소스 : SFML : 다양한 멀티미디어를 지원하는 API / 끄투DB : 다양한 주제의 단어를 지원하는 오픈소스
