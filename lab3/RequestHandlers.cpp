#include "Request.h"
#include <cstdio>
#include "EStore.h"

/*
 * ------------------------------------------------------------------
 * add_item_handler --
 *
 *      Handle an AddItemReq.
 *
 *      Delete the request object when done.
 *
 * Results:
 *      None.
 *
 * ------------------------------------------------------------------
 */
void 
add_item_handler(void *args)
{
    // TODO: Your code here.
    struct AddItemReq *a=(AddItemReq*) args;
   (a->store)->addItem(a->item_id, a->quantity, a->price, a->discount);//calling the method 
    printf("Handling AddItemReq: ");
    printf(", quantity -  %d" + a->quantity);
    printf(", price -  %lf" , a->price);
    printf(", discount -  %lf" , a->discount);
    printf(", item_id- %d ", a->item_id);

    printf("\n");
    a=NULL;
}
/*
 * ------------------------------------------------------------------
 * remove_item_handler --
 *
 *      Handle a RemoveItemReq.
 *
 *      Delete the request object when done.
 *
 * Results:
 *      None.
 *
 * ------------------------------------------------------------------
 */
void 
remove_item_handler(void *args)
{
    // TODO: Your code here.
    struct RemoveItemReq *b= (RemoveItemReq*) args;
    (b->store)->removeItem(b->item_id);
    printf("Handling RemoveItemReq: item_id -  %d " + b->item_id);
    printf("\n");
	b=NULL;
}
/*
 * ------------------------------------------------------------------
 * add_stock_handler --
 *
 *      Handle an AddStockReq.
 *
 *      Delete the request object when done.
 *
 * Results:
 *      None.
 *
 * ------------------------------------------------------------------
 */
void 
add_stock_handler(void *args)
{
    // TODO: Your code here.
    	struct AddStockReq *c= (AddStockReq*) args;
	(c->store)->addStock(c->item_id,c->additional_stock);
	printf("Handling AddStockReq: item_id -  %d" + c->item_id);
	printf(", additional_stock %d" + c->additional_stock);
	printf("\n");
	c=NULL;
}
/*
 * ------------------------------------------------------------------
 * change_item_price_handler --
 *
 *      Handle a ChangeItemPriceReq.
 *
 *      Delete the request object when done.
 *
 * Results:
 *      None.
 *
 * ------------------------------------------------------------------
 */
void 
change_item_price_handler(void *args)
{
    // TODO: Your code here.
    struct ChangeItemPriceReq *d= (ChangeItemPriceReq*) args;
    (d->store)->priceItem(d->item_id,d->new_price);
    printf("Handling ChangeItemPriceReq:  item_id -  %d" + d->item_id);
    printf(", new_price -  %lf" , d->new_price);
    printf("\n"); 
    d=NULL;
}

/*
 * ------------------------------------------------------------------
 * change_item_discount_handler --
 *
 *      Handle a ChangeItemDiscountReq.
 *
 *      Delete the request object when done.
 *
 * Results:
 *      None.
 *
 * ------------------------------------------------------------------
 */
void 
change_item_discount_handler(void *args)
{
    // TODO: Your code here.
    struct ChangeItemDiscountReq *e= (ChangeItemDiscountReq*) args;
    (e->store)->discountItem(e->item_id,e->new_discount);
    printf("Handling ChangeItemDiscountReq: item_id - %d" + e->item_id);
    printf(", new_discount - %lf" , e->new_discount);
    printf("\n"); 
    e=NULL;
}
/*
 * ------------------------------------------------------------------
 * set_shipping_cost_handler --
 *
 *      Handle a SetShippingCostReq.
 *
 *      Delete the request object when done.
 *
 * Results:
 *      None.
 *
 * ------------------------------------------------------------------
 */
void 
set_shipping_cost_handler(void *args)
{
    // TODO: Your code here.
    struct SetShippingCostReq *f= (SetShippingCostReq*) args;
    (f->store)->setShippingCost(f->new_cost);
    printf("Handling SetShippingCostReq: new_cost - %lf" , f->new_cost);
    printf("\n"); 
    f=NULL;

}
/*
 * ------------------------------------------------------------------
 * set_store_discount_handler --
 *
 *      Handle a SetStoreDiscountReq.
 *
 *      Delete the request object when done.
 *
 * Results:
 *      None.
 *
 * ------------------------------------------------------------------
 */
void
set_store_discount_handler(void *args)
{
    // TODO: Your code here.
    struct SetStoreDiscountReq *g= (SetStoreDiscountReq*) args;
    (g->store)->setStoreDiscount(g->new_discount);
    printf("Handling SetStoreDiscountReq: new_discount - %lf" , g->new_discount);
    printf("\n");
    g=NULL;
}
/*
 * ------------------------------------------------------------------
 * buy_item_handler --
 *
 *      Handle a BuyItemReq.
 *
 *      Delete the request object when done.
 *
 * Results:
 *      None.
 *
 * ------------------------------------------------------------------
 */
void
buy_item_handler(void *args)
{
    // TODO: Your code here.
    struct BuyItemReq *h= (BuyItemReq*) args;
    (h->store)->buyItem(h->item_id,h->budget);
    printf("Handling BuyItemReq: item_id - %d" + h->item_id);
    printf( ", budget - %lf" , h->budget);
    printf("\n");
    h=NULL;
}
/*
 * ------------------------------------------------------------------
 * buy_many_items_handler --
 *
 *      Handle a BuyManyItemsReq.
 *
 *      Delete the request object when done.
 *
 * Results:
 *      None.
 *
 * ------------------------------------------------------------------
 */
void
buy_many_items_handler(void *args)
{
    // TODO: Your code here.
 
    struct BuyManyItemsReq *j= (BuyManyItemsReq*) args;
   (j->store)->buyManyItems(&j->item_ids,j->budget);
    printf("Handling BuyManyItemsReq: item_ids - ");
   for(int i=0; i < (j->item_ids).size(); i++) 
	   printf("%d ", j->item_ids[i]);
   printf("\n");
   j=NULL;
}
/*
 * ------------------------------------------------------------------
 * stop_handler --
 *
 *      The thread should exit.
 *
 * Results:
 *      None.
 *
 * ------------------------------------------------------------------
 */
void 
stop_handler(void* args)
{
    // TODO: Your code here.
    printf("Handler StopHandlerReq: Quitting");
    printf("\n");
}
