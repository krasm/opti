/**
 * Node version
 */

fs = require('fs');


fs.readFile(process.argv[2], 'utf8', function (err, rawData) {
    var getNumbers = function(str) {
        var a = str.split(/\s+/);
        var ret = [];
        ret.push(Number(a[0]));
        ret.push(Number(a[1]));
                       
        return ret;
    }
    
    var max_profit = -1;
    var num_best = 0;
    var solution = [];

    var promising = function(idx, profit, weight) {
        if(weight >= K)  {
            return false;
        }
        
        while(idx < N && weight + items[idx].weight <= K) {
            weight += items[idx].weight;
            profit += items[idx].value;
            
            idx++;
        }

        if(idx < N) { 
            profit += Math.floor( (K - weight) * items[idx].ratio );
        }

        return profit >= max_profit;;
    }

    var solve = function(idx, profit, weight, included) {
        if(weight <= K && profit > max_profit) {
            max_profit = profit;
            num_best = idx;
            solution = included.slice(0);
        }
        if(idx < N && promising(idx, profit, weight)) {            
            included[idx] = 1;
            solve(idx+1, profit + items[idx].value, weight + items[idx].weight, included);
            included[idx] = 0;
            solve(idx+1, profit, weight, included);
        }
    }
    
    if (err) {
        return console.log(err);
    }
    //    console.log(rawData);
    
    var data = rawData.split('\n');
    var t = getNumbers(data[0]);
    var N = t[0];
    var K = t[1];
    var items = [];

    for(var i = 1; i <= N; i++) {
        var v, w;
        t = getNumbers(data[i]);
        v = t[0]; w = t[1];
        items.push({value:v, weight:w, ratio:(v/w)});
    }

    items.sort(function(lhs, rhs) {
        if(lhs.ratio > rhs.ratio) return -1;
        else if(lhs.ratio < rhs.ratio) return 1;
        return 0;
    });

    solve(0, 0, 0, new Array(N));

    console.log( max_profit );
    console.log(solution.join(' '));
});
