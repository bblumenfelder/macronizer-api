
/*MA****************************************************************/
/*                                                                 */
/*     File: SymbolTable.h                                         */
/*   Author: Helmut Schmid                                         */
/*  Purpose:                                                       */
/*  Created: Thu Jan  2 14:55:10 2003                              */
/* Modified: Tue Jul 28 16:38:45 2015 (schmid)                     */
/*                                                                 */
/*ME****************************************************************/

#ifndef _SYMBOL_TABLE
#define _SYMBOL_TABLE

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#include <vector>
using std::vector;

#include "sgi.h"

typedef unsigned int SymNum;
const size_t MaxSymNum = UINT_MAX;


/*****************  class SymbolTable  *****************************/

class SymbolTable {

private:

  struct eqstr {
    bool operator()(const char* s1, const char* s2) const {
      return strcmp(s1, s2) == 0;
    }
  };

  typedef hash_map<const char*, SymNum, hash<const char*>, eqstr> SymbolMap;

  SymbolMap ST;
  vector<char*> SN;

public:
  ~SymbolTable() {
    for( size_t i=0; i<SN.size(); i++ )
      free(SN[i]);
  }

  SymbolTable() {}

  SymbolTable( FILE *file ) {
    size_t n;
    fread( &n, sizeof(n), 1, file );
    char buffer[10000];
    for( size_t i=0; i<n; i++ ) {
      for( char *p=buffer; (*p = (char)fgetc(file)); p++ ) ;
      number(buffer);
    }
  }

  SymbolTable( SymbolTable &tab, const char *s, size_t n) {
    // Copy the symbols from tab to this table
    for( SymNum i=0; i<tab.size(); i++ )
      number(tab.name(i));

    // Add n additional symbols which consist of the string s 
    // followed by a number in the range between 0 and n-1
    for( size_t i=0; i<n; i++ ) { // create the additional n symbols
      char buffer[1000];
      sprintf(buffer,"%s%d", s, (int)i);
      number(buffer);
    }
  }

  void store( FILE *file ) const {
    size_t n=SN.size();
    fwrite( &n, sizeof(n), 1, file );
    for( size_t i=0; i<n; i++ ) {
      char *p = SN[i]; 
      do { fputc( *p, file ); } while (*(p++));
    }
  }

  void print( FILE *file ) const {
    for( size_t i=0; i<SN.size(); i++ )
      fprintf(file,"%s -> %u\n", SN[i], (unsigned)i);
  }

  SymNum number( const char *s ) {
    SymbolMap::iterator it=ST.find(s);
    if (it != ST.end())
      return it->second;

    // insert the new symbol into the tables
    char *r = strdup(s);
    size_t n = SN.size();
    if (n > MaxSymNum)
      throw("too many grammar symbols!");
    SN.push_back(r);
    ST[r] = (SymNum)n;
    return (SymNum)n;
  }

  bool lookup( const char *s, SymNum &result ) {
    SymbolMap::iterator it=ST.find(s);
    if (it == ST.end())
      return false;
    result = it->second;
    return true;
  }

  const char *name( SymNum n ) const {
    if (n < SN.size())
      return SN[n];
    return NULL;
  }

  typedef SymbolMap::iterator iterator;

  iterator find( const char *s ) { return ST.find(s); }
  iterator begin() { return ST.begin(); }
  iterator end()   { return ST.end(); }
  size_t   size() const { return ST.size(); }
};

#endif
