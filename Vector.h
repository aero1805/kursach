class Vector
{
public:
	float x, y;
	Vector() { x = 0; y = 0; };
	Vector(float, float);
	~Vector() {};
	Vector(const Vector&);
	Vector& operator + (Vector&);
	Vector& operator - (Vector&);
	void operator = (Vector&);
	Vector& operator * (float);
};

Vector::Vector(float a, float b)
{
	x = a; y = b;
}
Vector& Vector::operator+(Vector& a)
{
	Vector b(x + a.x, y + a.y);
	return b;
}
Vector& Vector::operator-(Vector& a)
{
	Vector b(x - a.x, y - a.y);
	return b;
}
void Vector::operator = (Vector& a)
{
	x = a.x;
	y = a.y;
}
Vector::Vector(const Vector& a)
{
	x = a.x;
	y = a.y;
}
Vector& Vector::operator*(float a)
{
	Vector b(x*a, y*a);
	return b;
}
