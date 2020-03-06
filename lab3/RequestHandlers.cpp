#include "Request.h"
#include <cstdio>
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
// AddItemReq.price=args.price;
//AddItemReq obj=new AddItemReq;

//obj.handler(args);

struct AddItemReq *a= (AddItemReq*) args;
printf("Handling AddItemReq: item_id -  %d" + a->item_id);
printf(", quantity -  %d" + a->quantity);
printf(", price -  %.2f" , a->price);
printf(", discount -  %.2f" , a->discount);




//printf("Handling AddItemreq:"+ " item_id - "+item_id+", quantity - "+quantity+", price:"+price+", discount - "+discount+);

//struct AddItemReq obj;
//obj.price=args.price;

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
struct RemoveItemReq *b= (RemoveItemReq*) args;
printf("Handling RemoveItemReq: item_id -  %d" + b->item_id);

    // TODO: Your code here.
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
struct AddStockReq *a= (AddStockReq*) args;
printf("Handling AddStockReq: item_id -  %d" + a->item_id);
printf(", additional_stock %d" + a->additional_stock);



    // TODO: Your code here.
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
struct ChangeItemPriceReq *a= (ChangeItemPriceReq*) args;
printf("Handling ChangeItemPriceReq:  item_id -  %d" + a->item_id);
printf(", new_price -  %.2f" , a->new_price);
 
   // TODO: Your code here.
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
struct ChangeItemDiscountReq *a= (ChangeItemDiscountReq*) args;
printf("Handling ChangeItemDiscountReq:  item_id -  %d" + a->item_id);
printf(", new_discount -  %.2f" , a->new_discount);
 


    // TODO: Your code here.
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
struct SetShippingCostReq *a= (SetShippingCostReq*) args;
printf("Handling SetShippingCostReq:  new_cost -  %.2f" , a->new_cost);
 


    // TODO: Your code here.
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
struct SetStoreDiscountReq *a= (SetStoreDiscountReq*) args;
printf("Handling SetStoreDiscountReq:  new_discount -  %.2f" , a->new_discount);


    // TODO: Your code here.
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
struct BuyItemReq *a= (BuyItemReq*) args;
printf("Handling BuyItemReq:  item_id -  %d" + a->item_id);
printf(", budget - %.2f" , a->budget);




    // TODO: Your code here.
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
//struct BuyManyItemsReq *a= (BuyManyItemsReq*) args;
//printf("Handling BuyManyItemsReq: item_ids -  %d" + a->item_ids);
//printf(", budget - %s" + a->budget);

  // TODO: Your code here.
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
//strcut AddItemReq *a= (AddItemReq*) args;
//printf("AddItemReq item_id: %d"+ a->item_id);
//printf("quantity: %d"+  a->quantity);
//printf("price: %s"+ a->price);
//printf(",discount: %s"+ a->discount);

printf("Handling StopHandlerReq: Quitting");

    // TODO: Your code here.
}

