
/*!
 *    _________               /\  
 *   /   _____/__ ____________)/  
 *   \_____  \|  |  \____ \__  \  
 *   /        \  |  /  |_> > __ \_
 *  /_______  /____/|   __(____  /
 *          \/      |__|       \/  
 *
 *  \author    Michael E. Cotterell <mepcott@uga.edu>
 *  \date      2016-10-25
 */

#ifndef NOPE_H
#define NOPE_H

#include <string>
#include <cerrno>
#include <cstring>

using std::string;

/**
 * Error handling function. This function does the same thing as `perror(3)`
 * by default, with options to terminate when executed as well as accept an
 * arbitrary errno.
 * @param prefix  prefix string
 * @param term    terminate if true
 * @param errnum  custom errno value
 */
inline void nope_out(const string & prefix = "", bool term = true, int errnum = errno) {
  if (prefix == "") fprintf(stderr, "%s\n", strerror(errnum));
  else              fprintf(stderr, "%s: %s\n", prefix.c_str(), strerror(errnum));
  if (term) exit(EXIT_FAILURE);
} // nope_out

#endif

