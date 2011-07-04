#include <lua5.1/lua.hpp>

namespace bange{
    
    class box{
        private:
            lua_State *vm;
        public:
            box();
            box(const char *);
            ~box();
        protected:
            void Initialize();
    };
    
}
