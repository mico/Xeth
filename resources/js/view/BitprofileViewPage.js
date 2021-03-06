var BitprofileViewPageView = SubPageView.extend({

    initialize:function(options){
        _(this).bindAll("open", "update", "updateURI", "updateDetails", "updateStealth", "showLoader", "hideLoader", "copyUriToClipboard");
		SubPageView.prototype.initialize.call(this,options);
        this.template = options.templates.get("view_bitprofile");
        this.$el.html(this.template());
        this.profiles = options.profiles;
        this.router = options.router;
        this.clipboard = options.clipboard;
    },
    
    render:function(){
        this.$el.html(this.template());
        this.$el.find(".btnURI").click(this.copyUriToClipboard);
    },
    
    exit:function(){
        if(this.model){
            this.stopListening(this.model);
        }
    },

    open:function(args){
        this.exit();
        this.model = this.profiles.find({uri:args.uri});
        this.update();
        this.listenTo(this.model, "change:uri", this.updateURI);
        this.listenTo(this.model, "change:details",this.updateDetails);
        this.listenTo(this.model, "change:payments", this.updateStealth);
    },
    
    update:function(model){
        this.updateURI();
        this.updateDetails();
        this.updateStealth();
        if(!this.model.get("loaded")){
            this.showLoader();
            this.model.once("change:loaded", this.hideLoader);
        }
    },
    
    updateURI:function(){
        this.$el.find(".contextSelect input").val(this.model.get("context"));
        this.$el.find(".bitprofileID input").val(this.model.get("id"));
    },
    
    updateDetails:function(){
        var details = this.model.get("details")||{};
        this.$el.find(".avatar img").attr("src",((details && details.avatar)?details.avatar:'img/avatarEmpty.png'));
        this.$el.find("input.name").val((details && details.name) ? details.name : "");
    },

    updateStealth:function(){
        var stealth = this.model.get("payments");
        this.$el.find(".stealthAddress .address").html(((stealth)?shortify(stealth, 21):'Stealth Account not linked'));
    },

    showLoader:function(){
        this.$el.find(".loader").addClass("pending");
    },

    hideLoader:function(){
        this.$el.find(".loader").removeClass("pending");
    },

    copyUriToClipboard:function(){
        this.clipboard.setText(this.model.get("uri"));
        notifySuccess("uri copied");
    }

});
