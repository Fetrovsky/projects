// Copyright (C) 2011, Daniel Valencia (Fetrovsky)

#ifndef PROPERTY_H_INCLUDED
#define PROPERTY_H_INCLUDED

#define DECLARE_ARRAY(T, N) extern T N[]; extern size_t N##Count

#define DEFINE_ARRAY(T, N) DECLARE_ARRAY(T, N); \
                           T N[] =

#define DEFINE_ARRAY_SIZE(N) size_t N##Count = sizeof(N)/sizeof(N[0])


#define GETTER(T, N) T& N() { return _##N; }
#define CONST_GETTER(T, N) T const& N() const { return _##N; }

#define PROPERTY(T, N) private: T _##N; \
                       public: CONST_GETTER(T, N) \
                               GETTER(T, N)

#define PROTECTED_PROPERTY(T, N) protected: T _##N; \
                                 public: CONST_GETTER(T, N) \
                                         GETTER(T, N)

#define CONST_PROPERTY(T, N) private: T const _##N; \
                             public: CONST_GETTER(T, N)

#define PROTECTED_CONST_PROPERTY(T, N) protected: T _##N; \
                                       public: CONST_GETTER(T, N)

#define READ_ONLY_PROPERTY(T, N) private: T _##N; \
                                 public: CONST_GETTER(T, N)

#define STRING_PROPERTY(N) PROPERTY(std::string, N)
#define CONST_STRING_PROPERTY(N) CONST_PROPERTY(std::string, N)

#endif  // PROPERTY_H_INCLUDED

