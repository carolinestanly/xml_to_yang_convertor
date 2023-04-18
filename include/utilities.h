#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdio.h>
#include <ctype.h>
#include <float.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <glib.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include "attrs_handler.h"
#include "leaf_handler.h"
#include "container_handler.h"
#include "list_handler.h"

// Macros for the YANG module 
#define TABLE_SIZE 1000000
#define FLOAT_TYPE "decimal64"
#define STRING_TYPE "string"
#define FLOAT_RANGE "range 1..1024"
#define EMPTY_STRING "";

#define INT8 "int8"
#define INT16 "int16"
#define INT32 "int32"
#define INT64 "int64"
#define UINT8 "uint8"
#define UINT16 "uint16"
#define UINT32 "uint32"
#define UINT64 "uint64"
#define DECIMAL32 "decimal32"
#define DECIMAL64 "decimal64"
#define DECIMAL128 "decimal128"

#define INT8_RANGE "range -128..127"
#define INT16_RANGE "range -32768..32767"
#define INT32_RANGE "range -2147483648..2147483647"
#define INT64_RANGE "range -9223372036854775808..9223372036854775807"
#define UINT8_RANGE "range 0..255"
#define UINT16_RANGE "range 0..65535"
#define UINT32_RANGE "range 0..4294967295"
#define UINT64_RANGE "range 0..18446744073709551615"

#define PLUS_SIGN '+'
#define MINUS_SIGN '-'
#define SPACE ' '
#define DOT '.'
#define STRING_LENGTH 16

// The number of digits after the decimal point
typedef enum
{
  DECIMAL_DIG_2 = 2,
  DECIMAL_DIG_4 = 4,
  DECIMAL_DIG_7 = 7,
  DECIMAL_DIG_9 = 9,
  DECIMAL_DIG_16 = 16
} DecimalDigits;

// The type of the values
typedef struct
{
  const char *type;
  const char *range;
  const char *length;
} TypeRange;

// The type of the values
TypeRange get_number_type(const xmlChar *content);

// The number of digits after the decimal point
bool is_list_element(xmlNode *node);

// find the first child element of a node
xmlNode *find_first_child_element(xmlNode *node);

//serialize the list node and its children recursively
void serializeList(xmlNode *node, int depth, FILE *yang_file, GHashTable *printed_elements);

// export the input xml file to yang
void exportXmlToYang(xmlNode *node, int depth, GHashTable *printed_elements, FILE *yang_file);

// read the config file
void read_config(const char *config_filename, char *module_name, char *namespace, char *prefix, char *revision);

#endif // UTILITIES_H