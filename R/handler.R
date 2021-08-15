
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

