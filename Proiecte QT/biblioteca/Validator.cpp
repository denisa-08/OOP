//
//
//

#include "Validator.h"
#include <cassert>
#include <sstream>

void BookValidator::validate(const Book& b) {
    vector<string> msgs;
    if(b.getTitle().size() == 0) msgs.push_back("Titlu vid!!!");
    if(b.getAuthor().size() == 0) msgs.push_back("Autor vid!!!");
    if(b.getGenre().size() == 0) msgs.push_back("Gen vid!!!");
    if(b.getYear() < 1500) msgs.push_back("An invalid!!!");
    if(msgs.size() > 0)
        throw ValidateException(msgs);
}

/*void testValidator() {
    BookValidator val;
    Book b { "", "a1", "g1", 1900};
    try {
        val.validate(b);
        assert(false);
    }
    catch (ValidateException) {
        assert(true);
    }


}*/
