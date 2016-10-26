#include "productsmanager.h"

ProductsManager::ProductsManager()
{

}

void ProductsManager::insert(Product *prod)
{
    this->appendRow(prod);
}
