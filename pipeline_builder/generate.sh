# Get script directory
DIR=`dirname "$(readlink -f "$0")"`
# Change directory to script root
cd "$DIR"

# Remove previous backup 
if [[ -d generated_backup ]]; then
    rm -r generated_backup
fi

# If previous generated folder exists
if [[ -d generated ]]; then
    # Create a backup
    cp -r generated generated_backup

    # Clean current generated
    rm -r generated
fi

# Prepare clean folder
mkdir -p generated/depthai-shared/generated

# Create a list of files to generate
list=`echo global/Global.properties.schema.json nodes/*/*.properties.schema.json common/ProcessorType.schema.json schema/Pipeline.schema.json`

# Generate sources
quicktype --namespace dai::gen --member-style camel-case --code-format with-struct --source-style multi-source --include-location global-include -s schema -l c++ -o "generated/depthai-shared/generated/PipelineBuilderGenerated.hpp" $list