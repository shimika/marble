#include <string>
using namespace	std;

string neko =
"＿ ＿"
"＿(＼"
", ' : : : : :＼　　　　＼ノヽ"
"/ : : : : l : : : : : : ＼＿＿ノ __ | _"
"/ ヽ--''ヽ : : : : ヾヽ : !: ::ヽ　ヽ /"
"（・ω・｀　）＼ : : : ヽi : ｌ : : : | ＼ / ゝ"
"		   ∈二　∈二　 　 ~~| : ; | ）: ﾉ 　 ´"
"{ ﾖ　　　E]ヽ　.j::ﾉ: : ８x"
"ｌ | 辷 ',-イく_~　l: :|"
"丶!ト　^´, , イ',　!: :l"
"!| ｀ - ´　 | \"　!: :l\""
"!__(_　i -= -‐t┘　 | : : ',"
"∪　 / ∪ i　i　i.).l : : ',"
"（_, （_, _二二[つ　 ヽ从";

string getpicture(char num) {
	switch (num) {
		case 1:
			return neko;
		default:
			break;
	}
}