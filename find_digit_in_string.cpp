string text="Der bisherige Standard C++98 ist nach 13
Jahren am 12. August 2011 durch den neuen Standard C++11
abgelöst worden."
regex regNumb(r"(\d+)");
sregex_token_iterator it(text.begin(),text.end(),regNumb);
sregex_token_iterator end;
while (it != end) cout << *it++ << " ";
