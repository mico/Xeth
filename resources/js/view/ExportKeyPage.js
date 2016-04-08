var ExportKeyPageView = SubPageView.extend({

    initialize:function(options){
        _(this).bindAll("submit");
		SubPageView.prototype.initialize.call(this,options);
        this.filesystem = options.filesystem;
        this.template = options.templates.get("export");
        this.router = options.router;
        
        this.accounts = new AccountSelect({collection:options.accounts, templates:options.templates});
        this.accounts.filter(function(model){ return model!=undefined;});
    },

    render:function(){
        this.$el.html(this.template());
        this.$el.find(".btnSubmit").click(this.submit);
        
        this.accounts.compact(false);
        this.accounts.resize(); //default size
        this.accounts.attach(this.$el.find("#exportAddress_account"));
    },

    submit:function(){
        var path = this.filesystem.browse();
        var model = this.accounts.selected();
        if(!model.backup(path)){
            notifyError("failed to backup, please check disk space");
            return false;
        }
        notifySuccess("key exported");
        this.router.redirect(); //go to default page
        return true;
    }

});
