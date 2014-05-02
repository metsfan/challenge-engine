void main(vec2 &in position)
{
	print("Position: " + position.x + "," + position.y);

	vec2 anotherVec;
	anotherVec.x = 3;
	anotherVec.y = 7;

	//vec2 copy = anotherVec;
	//anotherVec += 7.0;
	vec2 copy = anotherVec * 7.0;

	print("Result: " + copy.x + "," + copy.y);
}