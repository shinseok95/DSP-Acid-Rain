// #include "Game.cpp"
// #include <SFML/Graphics.hpp>
// #include <iostream>
// #include <string>
// using namespace sf;

// int cho = -1, jung = -1, jong = -1;

// void combi(std::wstring &Textbox) {
//     int com;
//     if (cho < 0)
//         return;
//     else if (jung < 0)
//         return;
//     else if (jong < 0)
//         com = 44032 + (cho * 588) + (jung * 28);
//     else
//         com = 44032 + (cho * 588) + (jung * 28) + jong;
//     Textbox += com;
//     cho = -1, jung = -1;
//     jong = -1;
// }

// int tempcombi() {
//     int com;
//     if (cho < 0)
//         return 0;
//     else if (jung < 0) {
//         switch (cho) {
//         case 0:
//             return 12593;
//             break;
//         case 1:
//             return 12594;
//             break;
//         case 2:
//             return 12596;
//             break;
//         case 3:
//             return 12599;
//             break;
//         case 4:
//             return 12600;
//             break;
//         case 5:
//             return 12601;
//             break;
//         case 6:
//             return 12609;
//             break;
//         case 7:
//             return 12610;
//             break;
//         case 8:
//             return 12611;
//             break;
//         case 9:
//             return 12613;
//             break;
//         case 10:
//             return 12614;
//             break;
//         case 11:
//             return 12615;
//             break;
//         case 12:
//             return 12616;
//             break;
//         case 13:
//             return 12617;
//             break;
//         case 14:
//             return 12618;
//             break;
//         case 15:
//             return 12619;
//             break;
//         case 16:
//             return 12620;
//             break;
//         case 17:
//             return 12621;
//             break;
//         case 18:
//             return 12622;
//             break;
//         default:
//             return 0;
//         }
//     } else if (jong < 0)
//         com = 44032 + (cho * 588) + (jung * 28);
//     else
//         com = 44032 + (cho * 588) + (jung * 28) + jong;
// }

// void typeWord(/*std::wstring &Textbox,*/ sf::Event event, Uint32 uni,
//               Game &game) {

//     Font f;
//     f.loadFromFile("Nanum.ttf");
//     Text t;
//     Text result;
//     uni = event.text.unicode;

//     if ((uni >= 'a' && uni <= 'z') || uni == 'Q' || uni == 'W' || uni == 'E'
//     ||
//         uni == 'R' || uni == 'T' || uni == 'O' || uni == 'P') {
//         if (cho < 0) {
//             switch (uni) {
//             case 'r':
//                 cho = 0;
//                 break;
//             case 'R':
//                 cho = 1;
//                 break;
//             case 's':
//                 cho = 2;
//                 break;
//             case 'e':
//                 cho = 3;
//                 break;
//             case 'E':
//                 cho = 4;
//                 break;
//             case 'f':
//                 cho = 5;
//                 break;
//             case 'a':
//                 cho = 6;
//                 break;
//             case 'q':
//                 cho = 7;
//                 break;
//             case 'Q':
//                 cho = 8;
//                 break;
//             case 't':
//                 cho = 9;
//                 break;
//             case 'T':
//                 cho = 10;
//                 break;
//             case 'd':
//                 cho = 11;
//                 break;
//             case 'w':
//                 cho = 12;
//                 break;
//             case 'W':
//                 cho = 13;
//                 break;
//             case 'c':
//                 cho = 14;
//                 break;
//             case 'z':
//                 cho = 15;
//                 break;
//             case 'x':
//                 cho = 16;
//                 break;
//             case 'v':
//                 cho = 17;
//                 break;
//             case 'g':
//                 cho = 18;
//                 break;
//             }
//         } else if (jung < 0) {
//             switch (uni) {
//             case 'k':
//                 jung = 0;
//                 break;
//             case 'o':
//                 jung = 1;
//                 break;
//             case 'i':
//                 jung = 2;
//                 break;
//             case 'O':
//                 jung = 3;
//                 break;
//             case 'j':
//                 jung = 4;
//                 break;
//             case 'p':
//                 jung = 5;
//                 break;
//             case 'u':
//                 jung = 6;
//                 break;
//             case 'P':
//                 jung = 7;
//                 break;
//             case 'h':
//                 jung = 8;
//                 break;
//             case 'y':
//                 jung = 12;
//                 break;
//             case 'n':
//                 jung = 13;
//                 break;
//             case 'b':
//                 jung = 17;
//                 break;
//             case 'm':
//                 jung = 18;
//                 break;
//             case 'l':
//                 jung = 20;
//                 break;
//             }
//         } else if (jong < 0) {
//             switch (uni) {
//             case 'k':
//                 if (jung == 8)
//                     jung = 9;
//                 break;
//             case 'o':
//                 if (jung == 8)
//                     jung = 10;
//                 break;
//             case 'j':
//                 if (jung == 13)
//                     jung = 14;
//                 break;
//             case 'p':
//                 if (jung == 13)
//                     jung = 15;
//                 break;
//             case 'l':
//                 if (jung == 8)
//                     jung = 11;
//                 else if (jung == 13)
//                     jung = 16;
//                 else if (jung == 18)
//                     jung = 19;
//                 break;

//             case 'r':
//                 jong = 1;
//                 break;
//             case 'R':
//                 jong = 2;
//                 break;
//             case 's':
//                 jong = 4;
//                 break;
//             case 'e':
//                 jong = 7;
//                 break;
//             case 'E':
//                 combi(game.Textbox);
//                 cho = 4;
//                 break;
//             case 'f':
//                 jong = 8;
//                 break;
//             case 'a':
//                 jong = 16;
//                 break;
//             case 'q':
//                 jong = 17;
//                 break;
//             case 'Q':
//                 combi(game.Textbox);
//                 cho = 8;
//                 break;
//             case 't':
//                 jong = 19;
//                 break;
//             case 'T':
//                 jong = 20;
//                 break;
//             case 'd':
//                 jong = 21;
//                 break;
//             case 'w':
//                 jong = 22;
//                 break;
//             case 'W':
//                 combi(game.Textbox);
//                 cho = 13;
//                 break;
//             case 'c':
//                 jong = 23;
//                 break;
//             case 'z':
//                 jong = 24;
//                 break;
//             case 'x':
//                 jong = 25;
//                 break;
//             case 'v':
//                 jong = 26;
//                 break;
//             case 'g':
//                 jong = 27;
//                 break;
//             }
//         } else {
//             switch (uni) {
//             case 'r':
//                 if (jong == 8)
//                     jong = 9;
//                 else {
//                     combi(game.Textbox);
//                     cho = 0;
//                 }
//                 break;
//             case 'R':
//                 combi(game.Textbox);
//                 cho = 1;
//                 break;
//             case 's':
//                 combi(game.Textbox);
//                 cho = 2;
//                 break;
//             case 'e':
//                 combi(game.Textbox);
//                 cho = 3;
//                 break;
//             case 'E':
//                 combi(game.Textbox);
//                 cho = 4;
//                 break;
//             case 'f':
//                 combi(game.Textbox);
//                 cho = 5;
//                 break;
//             case 'a':
//                 if (jong == 8)
//                     jong = 10;
//                 else {
//                     combi(game.Textbox);
//                     cho = 6;
//                 }
//                 break;
//             case 'q':
//                 if (jong == 8)
//                     jong = 11;
//                 else {
//                     combi(game.Textbox);
//                     cho = 7;
//                 }
//                 break;
//             case 'Q':
//                 combi(game.Textbox);
//                 cho = 8;
//                 break;
//             case 't':
//                 if (jong == 1)
//                     jong = 3;
//                 else if (jong == 8)
//                     jong = 12;
//                 else if (jong == 17)
//                     jong = 18;
//                 else {
//                     combi(game.Textbox);
//                     cho = 9;
//                 }
//                 break;
//             case 'T':
//                 combi(game.Textbox);
//                 cho = 10;
//                 break;
//             case 'd':
//                 combi(game.Textbox);
//                 cho = 11;
//                 break;
//             case 'w':
//                 if (jong == 4)
//                     jong = 5;
//                 else {
//                     combi(game.Textbox);
//                     cho = 12;
//                 }
//                 break;
//             case 'W':
//                 combi(game.Textbox);
//                 cho = 13;
//                 break;
//             case 'c':
//                 combi(game.Textbox);
//                 cho = 14;
//                 break;
//             case 'z':
//                 combi(game.Textbox);
//                 cho = 15;
//                 break;
//             case 'x':
//                 if (jong == 8)
//                     jong = 13;
//                 else {
//                     combi(game.Textbox);
//                     cho = 16;
//                 }
//                 break;
//             case 'v':
//                 if (jong == 8)
//                     jong = 14;
//                 else {
//                     combi(game.Textbox);
//                     cho = 17;
//                 }
//                 break;
//             case 'g':
//                 if (jong == 4)
//                     jong = 6;
//                 else if (jong == 8)
//                     jong = 15;
//                 else {
//                     combi(game.Textbox);
//                     cho = 18;
//                 }
//                 break;
//             default:
//                 int temp;
//                 switch (jong) {
//                 case 1:
//                     jong = 0;
//                     temp = 0;
//                     break;
//                 case 2:
//                     jong = 0;
//                     temp = 1;
//                     break;
//                 case 3:
//                     jong = 1;
//                     temp = 9;
//                     break;
//                 case 4:
//                     jong = 0;
//                     temp = 2;
//                     break;
//                 case 5:
//                     jong = 4;
//                     temp = 12;
//                     break;
//                 case 6:
//                     jong = 4;
//                     temp = 18;
//                     break;
//                 case 7:
//                     jong = 0;
//                     temp = 3;
//                     break;
//                 case 8:
//                     jong = 0;
//                     temp = 5;
//                     break;
//                 case 9:
//                     jong = 8;
//                     temp = 0;
//                     break;
//                 case 10:
//                     jong = 8;
//                     temp = 6;
//                     break;
//                 case 11:
//                     jong = 8;
//                     temp = 7;
//                     break;
//                 case 12:
//                     jong = 8;
//                     temp = 9;
//                     break;
//                 case 13:
//                     jong = 8;
//                     temp = 16;
//                     break;
//                 case 14:
//                     jong = 8;
//                     temp = 17;
//                     break;
//                 case 15:
//                     jong = 8;
//                     temp = 18;
//                     break;
//                 case 16:
//                     jong = 0;
//                     temp = 6;
//                     break;
//                 case 17:
//                     jong = 0;
//                     temp = 7;
//                     break;
//                 case 18:
//                     jong = 17;
//                     temp = 9;
//                     break;
//                 case 19:
//                     jong = 0;
//                     temp = 9;
//                     break;
//                 case 20:
//                     jong = 0;
//                     temp = 10;
//                     break;
//                 case 21:
//                     jong = 0;
//                     temp = 11;
//                     break;
//                 case 22:
//                     jong = 0;
//                     temp = 12;
//                     break;
//                 case 23:
//                     jong = 0;
//                     temp = 14;
//                     break;
//                 case 24:
//                     jong = 0;
//                     temp = 15;
//                     break;
//                 case 25:
//                     jong = 0;
//                     temp = 16;
//                     break;
//                 case 26:
//                     jong = 0;
//                     temp = 17;
//                     break;
//                 case 27:
//                     jong = 0;
//                     temp = 18;
//                     break;
//                 }
//                 combi(game.Textbox);
//                 cho = temp;
//                 switch (uni) {
//                 case 'k':
//                     jung = 0;
//                     break;
//                 case 'o':
//                     jung = 1;
//                     break;
//                 case 'i':
//                     jung = 2;
//                     break;
//                 case 'O':
//                     jung = 3;
//                     break;
//                 case 'j':
//                     jung = 4;
//                     break;
//                 case 'p':
//                     jung = 5;
//                     break;
//                 case 'u':
//                     jung = 6;
//                     break;
//                 case 'P':
//                     jung = 7;
//                     break;
//                 case 'h':
//                     jung = 8;
//                     break;
//                 case 'y':
//                     jung = 12;
//                     break;
//                 case 'n':
//                     jung = 13;
//                     break;
//                 case 'b':
//                     jung = 17;
//                     break;
//                 case 'm':
//                     jung = 18;
//                     break;
//                 case 'l':
//                     jung = 20;
//                     break;
//                 }
//             }
//         }
//     } else if (uni == 13 || uni == 32) {
//         combi(game.Textbox);
//         game.result.setString(game.Textbox);
//         game.Textbox.clear();
//     } else if (uni == 8) {
//         if (cho < 0)
//             game.Textbox = game.Textbox.substr(0, game.Textbox.size() - 1);
//         else if (jung < 0)
//             cho = -1;
//         else if (jong < 0)
//             jung = -1;
//         else
//             jong = -1;
//     }
// }
