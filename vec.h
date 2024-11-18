template<typename T, int N>
class vec
{
    private:
    T data[N] = {T(0)};

    public:
    vec() = default;
    ~vec() = default;

    vec(T a, T b){
        data[0] = a;
        data[1] = b;
    }

    vec(T a, T b, T c){
        data[0] = a;
        data[1] = b;
        data[2] = c;
    }

    vec(const vec<T, N>& v1){
        for(int i = 0; i < N; i++){
            data[i] = v1[i];
        }
    }

    // template<typename... Args>
    // vec(Args&&... args):
    //     data{args...}
    // {}

    vec<T, N> operator+(const vec<T, N>& v1){
        vec<T, N> res;
        for(int i = 0; i < N; i++){
            res[i] = this->data[i] + v1[i];
        }
        return res;
    }

    vec<T, N> operator-(const vec<T, N>& v1){
        vec res;
        for(int i = 0; i < N; i++){
            res.data[i] = this->data[i] - v1.data[i];
        }
        return res;
    }

    vec<T, N> operator-(){
        vec res;
        for(int i = 0; i < N; i++){
            res.data[i] = - this->data[i];
        }
        return res;
    }

    T operator*(const vec<T, N>& v1){
        T res = 0;
        for(int i = 0; i < N; i++){
            res += this->data[i] * v1.data[i];
        }
        return res;
    }

    const T& operator[](int i) const{
        return data[i];
    }

    T& operator[](int i){
        return data[i];
    }

};

