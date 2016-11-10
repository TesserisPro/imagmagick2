var magic = require("./build/Release/imagemagick");

function Wand(fileName, loadedProgress) {
    var self = this;
    self.file = fileName;
    self.actions = [];
    self.wand = null;
    self.reject = null;
    self.resolve = null;

    self.apply = function(finished) {
        if(self.wand)
            throw new Error("You can not use same image twice.");
        return new Promise(function(resolve, reject){
            self.resolve = resolve;
            self.reject = reject;

            var actionList = self.actions;//.map(x => x);
        
            var processActions = function() {
                if(actionList.length){
                    var action = actionList.shift();
                    action.apply(self, [processActions]);
                } else {
                    if(self.wand) _ok.apply(self);
                    if(finished) finished(self);
                }
            };
            
            magic.load(self.file, function(error, wand) {
                if(error)
                    reject(error);
                if(!wand)
                    reject("Critical error during image loading. Possible memory leak.");
                self.wand = wand;
                if(loadedProgress) loadedProgress(self);
                processActions();
            });
        });
    }

    self.do = function(progress) {
        if(progress) progress(this);
        return _branch();
    }

    self.break = function() {
        this.actions.length = 0;
    }

    self.strip = function(progerss){
        _append(function(callback){
            var self = this;
            magic.strip(this.wand, function(error){
                if(error) _fail.apply(self, [error]);
                if(progress) progress(self);
                callback();
            });
        });
        return _branch();
    }

    self.brightnessHistogram = function(size, progress){
        if(typeof size != "number")
            throw new Error("Size should be defined");
        _append(function(callback){
            var self = this;
            magic.brightnessHistogram(this.wand, size, function(error, histogram){
                if(error) _fail.apply(self, [error]);
                if(progress) progress(self, histogram);
                callback();
            });
        });
        return _branch();
    }

    self.size = function(progress) {
        _append(function(callback){
            var size = magic.size(this.wand);
            if(progress) progress(this, size);
            callback();
        });
        return _branch();
    }

    self.resize = function(width, height, progress) {
        _append(function(callback){
            if (!width && !height) {
               if(progress) progress(this);
               callback();
               return;
            }
            if(!height) {
                var size = magic.size(this.wand);
                height = width / size.width * size.height;
            }
            if(!width) {
                var size = magic.size(this.wand);
                width = height / size.height * size.width;
            }
            var self = this;
            magic.resize(this.wand, width, height, function(error){
                if(error) _fail.apply(self, [error]);
                if(progress) progress(self);
                callback();
            });
        });

        return _branch();    
    }

    self.rotate = function(angle, progress) {
        _append(function(callback){
            if (typeof angle != "number") {
               if(progress) progress(this);
               callback();
               return;
            }

            var self = this;
            magic.rotate(this.wand, angle, function(error){
                if(error) _fail.apply(self, [error]);
                if(progress) progress(self);
                callback();
            });
        });

        return _branch();    
    }

    self.grayscale = function(progress) {
        _append(function(callback){
            var self = this;
            magic.grayscale(this.wand, function(error){
                if(error) _fail.apply(self, [error]);
                if(progress) progress(self);
                callback();
            });
        });

        return _branch();    
    }

    self.write = function(fileName, progress) {
        _append(function(callback){
            var self = this;
            magic.write(this.wand, fileName, function(error) {
                if(error) _fail.apply(self, [error]);
                if(progress) progress(self);
                callback();
            });
        });
        
        return _branch();
    }
    

    var _branch = function() {
        if(self.wand)
            return self;
        
        var branch = new Wand(fileName, loadedProgress);
        branch.actions = self.actions.map(x => x);
        return branch;
    }

    var _append = function(action){
        if(self.wand)
            self.actions.unshift(action);
        else
            self.actions.push(action);
    }

    var _ok = function(){
        //this.break();
        magic.close(this.wand);
        this.wand = null;
        this.resolve(this);
    }

    var _fail = function(error){
        this.break();
        magic.close(this.wand);
        this.wand = null;
        this.reject(error);
    }
}

module.exports = function(fileName, progress){
    return new Wand(fileName, progress); 
};
