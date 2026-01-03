void initTable(Table* table) {

}

void freeTable(Table* table) {
	FREE_ARRAY(Entry, table->entries, table->capacity);
	initTable(table);
}

bool tableSet(Table* table, ObjString* key, Value value) {
	Entry* entry = findEntry(table->entries, table->capacity, key);
	bool isNewKey = entry->key == NULL;
	if(isNewKey) table->count++;

	entry->key = key;
	entry->value = value;
	return isNewKey;
}
