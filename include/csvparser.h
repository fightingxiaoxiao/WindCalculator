/*
 *   Copyright (c) 2020 Chen Xiaoxiao
 *   All rights reserved.

 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at

 *   http://www.apache.org/licenses/LICENSE-2.0

 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */

#ifndef CSVPARSER_H
#define CSVPARSER_H

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct CsvRow {
    char **fields_;
    int numOfFields_;
} CsvRow;

typedef struct CsvParser {
    char *filePath_;
    char delimiter_;
    int firstLineIsHeader_;
    char *errMsg_;
    CsvRow *header_;
    FILE *fileHandler_;
	int fromString_;
	char *csvString_;
	int csvStringIter_;
} CsvParser;


// Public
CsvParser *CsvParser_new(const char *filePath, const char *delimiter, int firstLineIsHeader);
CsvParser *CsvParser_new_from_string(const char *csvString, const char *delimiter, int firstLineIsHeader);
void CsvParser_destroy(CsvParser *csvParser);
void CsvParser_destroy_row(CsvRow *csvRow);
const CsvRow *CsvParser_getHeader(CsvParser *csvParser);
CsvRow *CsvParser_getRow(CsvParser *csvParser);
int CsvParser_getNumFields(const CsvRow *csvRow);
const char **CsvParser_getFields(const CsvRow *csvRow);
const char* CsvParser_getErrorMessage(CsvParser *csvParser);

// Private
CsvRow *_CsvParser_getRow(CsvParser *csvParser);    
int _CsvParser_delimiterIsAccepted(const char *delimiter);
void _CsvParser_setErrorMessage(CsvParser *csvParser, const char *errorMessage);

#ifdef __cplusplus
}
#endif

#endif
