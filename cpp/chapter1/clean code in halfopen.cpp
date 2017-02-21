template  <class Interpreter, class T)
Iterpreter find(Interpreter first, Interpreter last, const T &value){
	while(fist != last && *first != value)first++;
	return first;
}
template <class Interpreter, class T)
function for_each(Interpreter first, Interpreter last, function f){
	for(; first != last, ++first)f(*first);
	return f;
}
