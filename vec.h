#include <utility>

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

    // template <typename... Args>
    // requires(sizeof...(Args) == N && (std::convertible_to<Args, T> && ...))
    // explicit vec_n(Args&&... args) noexcept
    // : data{static_cast<T>(args)...} {}
    
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
            res.data[i] = this->data[i] - v1[i];
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
            res += this->data[i] * v1[i];
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

template<typename T, int N>
vec<T, N> operator*(const vec<T, N>& v, const T& a){
        vec<T, N> res;
        for(int i = 0; i < N; i++){
            res[i] = v[i]*a;
        }
        return res;
    }

template<typename T, int N>
vec<T, N> operator*(const T& a, const vec<T, N>& v){
        vec<T, N> res;
        for(int i = 0; i < N; i++){
            res[i] = v[i]*a;
        }
        return res;
    }

template<typename T, int N>
std::ostream& operator << (std::ostream &os, const vec<T, N>& v){
    std::ostream& res = os << "(" << v[0];
    for(int i = 1; i < N; i++){
        res << ", " << v[i];
    }
    res << ")";
    return res;
}