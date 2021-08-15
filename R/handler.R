
#' Title
#'
#' @return
#' @export
#' @importFrom wk new_wk_handler
#' @examples
#' bbox_handler()
bbox_handler <- function() {
  wk::new_wk_handler(cpp_bbox_handler_new(), "bbox_wk_handler")
}



#' Title
#'
#' @param input
#' @param handler
#'
#' @return
#' @export
#' @importFrom wk as_wk_handler
#' @examples
#' df <- data.frame(x = 1:3, y = 2:4)
#' handle_xy(df, wk::wkt_writer())
handle_xy <- function(input, handler) {
  input$x <- as.numeric(input$x)
  input$y <- as.numeric(input$y)
  cpp_handle_xy(input, wk::as_wk_handler(handler))
}

