Projekt wykonany w ramach przedmiotu Technika Mikroprocesorowa 2.

Autorzy projektu: Wojciech Gałecki, Karolina Rapacz

Prowadzący laboratorium: dr inż. Mariusz Sokołowski

Link do filmiku pokazującego możliwości robota: https://www.youtube.com/watch?v=DRhq94w-HD8&lc=z231vrthcnanvvgeracdp431vruxp345r20q223zkmpw03c010c

Tematem naszego projektu było wykonanie robota wykorzystującego płytkę Kinetis FRDM-KL05Z, który autonomicznie pokona trasę w postaci labiryntu. Ze względu na ograniczone możliwości konstrukcji samego labiryntu, zamieściliśmy w filmie demo podstawowe sytuacje, w jakich pojazd znajdzie się w czasie przejazdu. Dodaliśmy także demonstrację zachowania poszczególnych czujników "w wolnej przestrzeni".

Robot opiera swoje działanie na trzech czujnikach odległości opartych o nadajnik i odbiornik podczerwieni oraz układ LM393, umieszczonych w jego przedniej części, odpowiednio po lewej stronie, z przodu i po prawej stronie. Dodatkowo posiada on dwa czujniki krańcowe, które mają obsługiwać przypadek uderzenia w ścianę, powodując odpowiednie wycofanie się pojazdu i korekcję jazdy.

Całość jest obsługiwana przez mikrokontroler Kinetis FRDM-KL05Z podłączony do shieldu przeznaczonego dla płytek kompatybilnych z Arduino. Dzięki zgodności wyprowadzeń KL05Z ze standardem Arduino, byliśmy w stanie wykonać połączenie 1:1. Wykorzystywany shield zawiera w sobie sterownik silników DC DRV8835, mostek H oraz buzzer z generatorem, a także kilka innych elementów, których nie wykorzystujemy w projekcie. Silniki DC napędzające koła są podłączone do shieldu, a szkielet został wykonany z drewnianej sklejki.

Dodatkowo korzystamy z diody RGB wchodzącej w skład KL05Z (sygnalizuje ona zderzenie w ścianę lub wyłączenie silników) oraz przycisku typu tact switch umieszczonego na małej płytce stykowej zamontowanej na szczycie konstrukcji robota (używanego do wyłączenia silników).

Robot jest zasilany poprzez zestaw baterii o łącznym napięciu wynoszącym ok. 9 V oraz poprzez przewód miniUSB. Podwójne zasilanie było wymagane ze względu na użycie elementów wymagających zasilania 5V, które Kinetis wystawia na pin wyłącznie przy zasilaniu przewodowym, przy czym silniki nie mogły być zasilane przez obwody mikrokontrolera z powodu zbyt dużych amplitud pobieranego prądu.
