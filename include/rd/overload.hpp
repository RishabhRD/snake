namespace rd {
template<typename... F> struct overload : F... { using F::operator()...; };
}// namespace rd
