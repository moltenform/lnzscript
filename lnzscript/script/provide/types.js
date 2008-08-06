
// from Douglas Crockford's little javascripter

isFunction = function(a) {
    return typeof a == 'function';
}

isArray = function(a) {
    return a && typeof a == 'object' && a.constructor == Array;
}

isNumber = function(a) {
    return isFinite(a);
}

