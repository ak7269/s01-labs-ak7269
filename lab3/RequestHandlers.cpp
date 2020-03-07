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
    struct AddItemReq *add=(AddItemReq*) args;
   (add->store)->addItem(add->item_id, add->quantity, add->price, add->discount);
    printf("Handling AddItemReq:\n");
    printf(".");
    printf(", quantity -  %d" + add->quantity);
    printf(", price -  %f" , add->price);
    printf(", discount -  %f" , add->discount);
    printf(", item_id- %d ", add->item_id);
    printf("\n");
	add=NULL;
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
    struct RemoveItemReq *r= (RemoveItemReq*) args;
    (r->store)->removeItem(r->item_id);
    printf(".");
    printf("Handling RemoveItemReq: item_id -  %d " + r->item_id);
    printf("\n");
	r=NULL;
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
    	struct AddStockReq *as= (AddStockReq*) args;
	(as->store)->addStock(as->item_id,as->additional_stock); 
	 printf(".");
	printf("Handling AddStockReq: item_id -  %d" + as->item_id);
	printf(", additional_stock %d" + as->additional_stock);
	printf("\n");
	as=NULL;
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
    struct ChangeItemPriceReq *c= (ChangeItemPriceReq*) args;
    (c->store)->priceItem(c->item_id,c->new_price);
     printf(".");
    printf("Handling ChangeItemPriceReq:  item_id -  %d" + c->item_id);
    printf(", new_price -  %lf" , c->new_price);
    printf("\n"); 
    c=NULL;
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
    struct ChangeItemDiscountReq *d= (ChangeItemDiscountReq*) args;
    (d->store)->discountItem(d->item_id,d->new_discount);
     printf(".");
    printf("Handling ChangeItemDiscountReq: item_id - %d" + d->item_id);
    printf(", new_discount - %lf" , d->new_discount);
    printf("\n"); 
    d=NULL;
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
    struct SetShippingCostReq *s= (SetShippingCostReq*) args;
    (s->store)->setShippingCost(s->new_cost);
     printf(".");
    printf("Handling SetShippingCostReq: new_cost - %lf" , s->new_cost);
    printf("\n"); 
    s=NULL;

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
    struct SetStoreDiscountReq *sd= (SetStoreDiscountReq*) args;
    (sd->store)->setStoreDiscount(sd->new_discount);
     printf(".");
    printf("Handling SetStoreDiscountReq: new_discount - %lf" , sd->new_discount);
    printf("\n");
    sd=NULL;
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
    struct BuyItemReq *a= (BuyItemReq*) args;
    (a->store)->buyItem(a->item_id,a->budget);
     printf(".");
    printf("Handling BuyItemReq: item_id - %d" + a->item_id);
    printf(", budget - %lf" , a->budget);
    printf("\n");
    a=NULL;
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
 
    struct BuyManyItemsReq *a= (BuyManyItemsReq*) args;
   (a->store)->buyManyItems(&a->item_ids,a->budget);
    printf("Handling BuyManyItemsReq: item_ids - ");
   for(int i=0; i < (a->item_ids).size(); i++) 
	   printf("%d ", a->item_ids[i]);
   printf("\n");
   a=NULL;
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
